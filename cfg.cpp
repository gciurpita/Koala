#include "Arduino.h"

#include "eng.h"
#include "vars.h"

const char *cfgFname = "/spiffs/koala.cfg";

const char *cfgMagic = "TLV";

// -------------------------------------
enum CfgId_e : byte {
    C_NONE,

    C_VER  = 1,

    C_NAME,
    C_SSID,
    C_PASS,
    C_HOST,
    C_PORT,

    C_L_00 = 100, C_L_01, C_L_02, C_L_03, C_L_04,
    C_L_05,       C_L_06, C_L_07, C_L_08, C_L_09,
    C_L_10,       C_L_11, C_L_12, C_L_13, C_L_14,
    C_L_15,       C_L_16, C_L_17, C_L_18, C_L_19,

    C_E_00 = 200, C_E_01, C_E_02, C_E_03, C_E_04,
    C_E_05,       C_E_06, C_E_07, C_E_08, C_E_09,
    C_E_10,       C_E_11, C_E_12, C_E_13, C_E_14,
    C_E_15,       C_E_16, C_E_17, C_E_18, C_E_19,
};

struct CfgHdr_s {
    CfgId_e id;
    byte    size;
};

#define HDR_SIZE    sizeof(CfgHdr_s)

// -------------------------------------
// stored (configurable) variable description
enum { V_NONE, V_STR, V_INT, V_LOCO, V_ENG };

struct CfgVar_s {
    CfgId_e     id;
    void       *p;
    byte        nByte;
    byte        type;
    const char *desc;
};

// -------------------------------------
//  stored variables

CfgVar_s cfgVarTbl [] = {
    { C_NAME, (void*)   name,       MAX_CHAR,     V_STR,  "name" },

    { C_SSID, (void*)   ssid,       MAX_CHAR,       V_STR,  "ssid"},
    { C_PASS, (void*)   pass,       MAX_CHAR,       V_STR,  "password" },
    { C_HOST, (void*)   host,       MAX_CHAR,       V_STR,  "hostname" },
    { C_PORT, (void*) & port,       sizeof(int),    V_INT,  "port" },

    { C_L_00, (void*) & locos [0],  sizeof(Loco_s), V_LOCO, "loco_1" },
    { C_L_01, (void*) & locos [1],  sizeof(Loco_s), V_LOCO, "loco_2" },
    { C_L_02, (void*) & locos [2],  sizeof(Loco_s), V_LOCO, "loco_3" },
    { C_L_03, (void*) & locos [3],  sizeof(Loco_s), V_LOCO, "loco_4" },
    { C_L_04, (void*) & locos [4],  sizeof(Loco_s), V_LOCO, "loco_5" },

    { C_L_05, (void*) & locos [5],  sizeof(Loco_s), V_LOCO, "loco_6" },
    { C_L_06, (void*) & locos [6],  sizeof(Loco_s), V_LOCO, "loco_7" },
    { C_L_07, (void*) & locos [7],  sizeof(Loco_s), V_LOCO, "loco_8" },
    { C_L_08, (void*) & locos [8],  sizeof(Loco_s), V_LOCO, "loco_9" },
    { C_L_09, (void*) & locos [9],  sizeof(Loco_s), V_LOCO, "loco_10" },

    { C_E_00, (void*) & engs  [0],  sizeof(Eng_s),  V_ENG,  "eng_0"  },
    { C_E_01, (void*) & engs  [1],  sizeof(Eng_s),  V_ENG,  "eng_1"  },
    { C_E_02, (void*) & engs  [2],  sizeof(Eng_s),  V_ENG,  "eng_2"  },
    { C_E_03, (void*) & engs  [3],  sizeof(Eng_s),  V_ENG,  "eng_3"  },

    { C_E_04, (void*) & engs  [4],  sizeof(Eng_s),  V_ENG,  "eng_4"  },
    { C_E_05, (void*) & engs  [5],  sizeof(Eng_s),  V_ENG,  "eng_5"  },
    { C_E_06, (void*) & engs  [6],  sizeof(Eng_s),  V_ENG,  "eng_6"  },
    { C_E_07, (void*) & engs  [7],  sizeof(Eng_s),  V_ENG,  "eng_7"  },

    { C_E_08, (void*) & engs  [8],  sizeof(Eng_s),  V_ENG,  "eng_8"  },
    { C_E_09, (void*) & engs  [9],  sizeof(Eng_s),  V_ENG,  "eng_9"  },
    { C_E_10, (void*) & engs [10],  sizeof(Eng_s),  V_ENG,  "eng_10" },
    { C_E_11, (void*) & engs [11],  sizeof(Eng_s),  V_ENG,  "eng_11" },

    { C_NONE, NULL,               0,              V_NONE, NULL     },
};

// ---------------------------------------------------------
CfgVar_s *
_cfgFindVar (
    CfgId_e  id )
{
    CfgVar_s *p;

    for (p = cfgVarTbl; C_NONE != p->id; p++)  {
        if (id == p->id)
            return p;
    }

    return NULL;
}

// -----------------------------------------------------------------------------
// zero out all cfg data for testing
void
cfgClr (void)
{
    printf ("%s:\n", __func__);

    for (CfgVar_s *p = cfgVarTbl; V_NONE != p->type; p++)  {
        bzero ((void*) p->p, p->nByte);
    }
};

// ---------------------------------------------------------
void
cfgDispLoco (
    Loco_s  *p )
{
     printf (" %6d %6.2f  %2d\n", p->adr, p->mphToDcc, p->engIdx);
};

// ---------------------------------------------------------
void
cfgDisp (
    Stream &Serial)
{
    printf ("%s:\n", __func__);

    for (CfgVar_s *p = cfgVarTbl; V_NONE != p->type; p++)  {
        switch (p->type)  {
        case V_INT:
            printf ("  %8s: %6d\n", p->desc, *(int*)p->p);
            break;

        case V_STR:
            printf ("  %8s: %s\n", p->desc, (char*)p->p);
            break;

        case V_ENG:
            printf ("  %8s:", p->desc);
            engDisp ((Eng_s*) p->p);
            break;

        case V_LOCO:
            printf ("  %8s:", p->desc);
            cfgDispLoco ((Loco_s*)p->p);
            break;
        }
    }
};

// ---------------------------------------------------------
char
cfgEditLoco (
    Loco_s      *p,
    const char  *desc)
{
    char s [100];
    do  {
        printf ("  %8s:", desc);
        cfgDispLoco (p);
        gets (s);

        sscanf (s, "%d %f %s", & p->adr, & p->mphToDcc, engs [p->engIdx].name);
    } while (strlen (s) && 'q' != s[0]);

    return s [0];
};

// ---------------------------------------------------------
void
cfgEdit (
    Stream &Serial)
{
    char s [100];
    char c;

    printf ("%s:\n", __func__);

    for (CfgVar_s *p = cfgVarTbl; V_NONE != p->type; )  {
        switch (p->type)  {
        case V_INT:
            printf ("  %8s: %6d\n", p->desc, *(int*)p->p);
            gets (s);
            c = s [0];
            if (strlen (s))
                *(int*)p->p = atoi (s);
            else
                p++;
            break;

        case V_STR:
            printf ("  %8s: %s\n", p->desc, (char*)p->p);
            gets (s);
            c = s [0];
            if (strlen (s))
                strcpy ((char*)p->p, s);
            else
                p++;
            break;

        case V_ENG:
            c = engEdit ((Eng_s*)p->p, p->desc);
            p++;
            break;

        case V_LOCO:
            c = cfgEditLoco ((Loco_s*) p->p, p->desc);
            p++;
            break;
        }

        if ('q' == c)
            break;
    }

    cfgDisp (Serial);
};

// ---------------------------------------------------------
int
cfgLoad (
    const char *filename )
{
    int res = 1;
    printf ("%s: %s\n", __func__, filename);

    FILE * fp = fopen (filename, "rb");
    if (NULL == fp)  {
        perror ("cfgLoad - fopen");
        res = 0;
        goto done;
    }

    // verify TLV file format
    byte magic [sizeof(cfgMagic)];

    if (1 != fread ((void*) & magic [0], sizeof(magic), 1, fp))  {
        perror ("cfgLoad - fread hdr\n");
        res = 0;
        goto done;
    };

    if (strncmp ((char*)magic, "TLV", sizeof(cfgMagic)))  {
        printf (" %s: non-TLV file\n", __func__);
        res = 0;
        goto done;
    }

    // read TLVs
    CfgHdr_s hdr;
    CfgVar_s *p;

    while (fread ((void*) &hdr, sizeof(hdr), 1, fp))  {
        if (0 == hdr.size)
            break;

        if (NULL == (p = _cfgFindVar (hdr.id)))  {
            printf (" %s: unknown cfgVar id, %d", __func__, hdr.id);
            break;
        }

        printf (" %s: %s\n", __func__, p->desc);

        // read amount written specified by hdr.size
        int nread = fread ((void*) p->p, hdr.size, 1, fp);
        if (! nread)  {
            printf (" %s: fread incomplete, %d %d",
                        __func__, nread, p->nByte);
            perror (" cfgLoad - fread");
            res = 0;
            goto done;
        }
    }

done:
    fclose (fp);
    return res;
}

// ---------------------------------------------------------
#if 1
void
cfgSave (
    const char *filename )
{
    printf ("%s: %s\n", __func__, filename);

    FILE * fp = fopen (filename, "wb+");
    if (NULL == fp)  {
        perror ("cfgSave - fopen");
        return;
    }

    if (1 != fwrite ((void*) cfgMagic, sizeof(cfgMagic), 1, fp)) {
        perror ("cfgSave: fwrite cfgMagic");
        goto done;
    }

    CfgHdr_s  hdr;
    for (CfgVar_s *p = cfgVarTbl; V_NONE != p->type; p++)  {
        hdr.id   = p->id;
        hdr.size = p->nByte;

        if (1 != fwrite ((void*) & hdr, sizeof(hdr), 1, fp)) {
            perror ("cfgSave: fwrite hdr");
            goto done;
        }

        int nwr = fwrite ((void*) p->p, p->nByte, 1, fp);
        if (! nwr)  {
            printf (" %s: fwrite incomplete, %d %d",
                        __func__, nwr, p->nByte);
            perror (" cfgSave - fwrite");
            return;
        }
    }

done:
    fclose (fp);
}
#endif
