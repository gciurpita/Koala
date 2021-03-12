#include "Arduino.h"

#include "eng.h"
#include "vars.h"

const char *cfgFname = "/spiffs/koala.dat";

// -------------------------------------
// stored (configurable) variable description
enum { V_NONE, V_STR, V_INT, V_LOCO, V_ENG };

struct CfgVar_s {
    void       *p;
    byte        nByte;
    byte        type;
    const char *desc;
};

// -------------------------------------
//  stored variables

CfgVar_s cfgVarTbl [] = {
    { (void*)   name,       MAX_CHAR,     V_STR,  "name" },

    { (void*)   ssid,       MAX_CHAR,       V_STR,  "ssid"},
    { (void*)   pass,       MAX_CHAR,       V_STR,  "password" },
    { (void*)   host,       MAX_CHAR,       V_STR,  "hostname" },
    { (void*) & port,       sizeof(int),    V_INT,  "port" },

    { (void*) & locos [0],  sizeof(Loco_s), V_LOCO, "loco_1" },
    { (void*) & locos [1],  sizeof(Loco_s), V_LOCO, "loco_2" },
    { (void*) & locos [2],  sizeof(Loco_s), V_LOCO, "loco_3" },

    { (void*) & locos [3],  sizeof(Loco_s), V_LOCO, "loco_4" },
    { (void*) & locos [4],  sizeof(Loco_s), V_LOCO, "loco_5" },
    { (void*) & locos [5],  sizeof(Loco_s), V_LOCO, "loco_6" },
    { (void*) & locos [6],  sizeof(Loco_s), V_LOCO, "loco_7" },

    { (void*) & locos [7],  sizeof(Loco_s), V_LOCO, "loco_8" },
    { (void*) & locos [8],  sizeof(Loco_s), V_LOCO, "loco_9" },
    { (void*) & locos [9],  sizeof(Loco_s), V_LOCO, "loco_10" },

    { (void*) & engs  [0],  sizeof(Eng_s),  V_ENG,   "eng_0"  },
    { (void*) & engs  [1],  sizeof(Eng_s),  V_ENG,   "eng_1"  },
    { (void*) & engs  [2],  sizeof(Eng_s),  V_ENG,   "eng_2"  },
    { (void*) & engs  [3],  sizeof(Eng_s),  V_ENG,   "eng_3"  },

    { (void*) & engs  [4],  sizeof(Eng_s),  V_ENG,   "eng_4"  },
    { (void*) & engs  [5],  sizeof(Eng_s),  V_ENG,   "eng_5"  },
    { (void*) & engs  [6],  sizeof(Eng_s),  V_ENG,   "eng_6"  },
    { (void*) & engs  [7],  sizeof(Eng_s),  V_ENG,   "eng_7"  },

    { (void*) & engs  [8],  sizeof(Eng_s),  V_ENG,   "eng_8"  },
    { (void*) & engs  [9],  sizeof(Eng_s),  V_ENG,   "eng_9"  },
    { (void*) & engs [10],  sizeof(Eng_s),  V_ENG,   "eng_10"  },
    { (void*) & engs [11],  sizeof(Eng_s),  V_ENG,   "eng_11"  },

    { NULL,               0,              V_NONE, NULL     },
};

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
     printf (" %6d, %6.2f, %s\n", p->adr, p->mphToDcc, p->engine);
};

// ---------------------------------------------------------
void
cfgDisp (void)
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

        sscanf (s, "%d %f %s", & p->adr, & p->mphToDcc, p->engine);
    } while (strlen (s) && 'q' != s[0]);

    return s [0];
};

// ---------------------------------------------------------
void
cfgEdit (void)
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

    cfgDisp ();
};

// ---------------------------------------------------------
void
cfgLoad (
    const char *filename )
{
    printf ("%s: %s\n", __func__, filename);

    FILE * fp = fopen (filename, "rb");
    if (NULL == fp)  {
        perror ("varsLoad - fopen");
        return;
    }

    for (CfgVar_s *p = cfgVarTbl; V_NONE != p->type; p++)  {
         int nread = fread ((void*) p->p, p->nByte, 1, fp);

        if (! nread)  {
            printf (" %s: fread incomplete, %d %d",
                        __func__, nread, p->nByte);
            perror (" varsLoad - fread");
            return;
        }
    }

    fclose (fp);
}

// ---------------------------------------------------------
#if 1
void
cfgSave (
    const char *filename )
{
    printf ("%s: %s\n", __func__, filename);

    FILE * fp = fopen (filename, "ab+");
    if (NULL == fp)  {
        perror ("cfgSave - fopen");
        return;
    }

    for (CfgVar_s *p = cfgVarTbl; V_NONE != p->type; p++)  {
         int nwr = fwrite ((void*) p->p, p->nByte, 1, fp);

        if (! nwr)  {
            printf (" %s: fwrite incomplete, %d %d",
                        __func__, nwr, p->nByte);
            perror (" cfgSave - fwrite");
            return;
        }
    }

    fclose (fp);
}
#endif
