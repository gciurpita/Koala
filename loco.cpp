// getLoco simulates retrieving a loco description by loco name

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "loco.h"
#include "koala.h"

Loco_t locos [] = {
   //  drvr    cyl-size   #   PSI   Adh   Tot   Tnd  Grate  BlrLn  BlrDi  BlrVol Pipe  Whyte      Name 
    {  61.5, 27.0, 32.0,  2,  220,  132,  146,   90,  95.0,  13.5,  88.0,      0, 0.0, "2-8-0",   "I-10sa"    },
    {  80.0, 25.0, 28.0,  2,  200,   90,  140,   90,  95.0,  19.0,  80.0,      0, 0.0, "4-6-2",   "G-1sas"    },
    {  61.5, 30.5, 32.0,  2,  220,  160,  200,  115, 108.0,  22.2, 100.0,      0, 0.0, "2-10-2",  "K-1"       },
    {  70.0, 27.0, 32.0,  2,  240,  126,  200,   90,  95.0,  13.5,  88.0,      0, 0.0, "4-8-4",   "T-1"       },
    {  36.0, 13.0, 18.0,  2,  180,   24,   34,    0,   9.0,  11.0,  40.0,      0, 8.0, "2-6-2T",  "NA_2-6-2"  },
    {  68.0, 23.8, 32.0,  4,  300,  270,  380,  170, 150.0,  18.0,  95.0,      0, 0.0, "4-8-8-4", "BigBoy"    },
    {  69.0, 22.0, 28.0,  2,  200,    0,    0,    0,   0.0,   0.0,   0.0,      0, 0.0, "_",       "catskill"  },
    {  84.0, 19.0, 28.0,  2,  300,   74,  140,  123,  69.0,  19.0,  80.0,      0, 0.0, "4-4-2",   "MILW_4-4-2"},
    {  80.0, 26.0, 28.0,  2,  225,   86,  187,  138,  80.0,  19.0,  80.0,      0, 0.0, "F-6",     "MILW_F-6"  },
    {  84.0, 23.5, 30.0,  2,  300,  108,  207,  187,  96.5,  19.0,  82.5,      0, 0.0, "F-7",     "MILW_F-7"  },
    {  70.0, 27.0, 32.0,  2,  320,  160,  247,  189, 107.7,   0.0,   0.0,      0, 0.0, "4-8-4",   "N&W"       },
};

#define N_LOCO   (sizeof(locos) / sizeof(Loco_t))

const char *locoFname = "/spiffs/loco.dat";

// ---------------------------------------------------------
void
locoDisp (void)
{
    printf ("%s:\n", __func__);

    Loco_t* p = locos;
    for (unsigned n = 0; n < N_LOCO; n++, p++)  {
        printf (" %2d:", n);
        printf (" %5.1f", p->drvrDia);
        printf (" %-10s", p->whyte);
        printf (" %s\n",    p->name);
    }
}

// ---------------------------------------------------------
Loco_t *
locoGet (
    char* name)
{
    Loco_t* p = locos;

    for (unsigned n = 0; n < N_LOCO; n++, p++)  {
        if (! strcmp(p->name, name))  {
            if (0 == p->BlrVol)  {
                p->BlrVol = p->BlrLen *
                        M_PI * (p->BlrDia / 24) * (p->BlrDia / 24);
            }

            return p;
        }
    }

    printf ("%s: ERROR - %s unknown\n", __func__, name);
    exit (2);
}

// ---------------------------------------------------------
void
locoSave (void)
{
    printf ("%s:\n", __func__);

    FILE * fp = fopen (locoFname, "w");
    if (NULL == fp)  {
        printf (" %s: fopen failed", __func__);
        return;
    }

    Loco_t* p = locos;

    for (int n = 0; N_LOCO > n; n++, p++)  {
        if (1 != fwrite ((void*) p, sizeof(Loco_t), 1, fp))  {
            printf (" %s: fwrite %d incomplete\n", __func__, n);
            break;
        }
    }

    fclose (fp);
}

// ---------------------------------------------------------
void
locoLoad (void)
{
    Loco_t* p = locos;

    printf ("%s:\n", __func__);

    FILE * fp = fopen (locoFname, "r");
    if (NULL == fp)  {
        locoSave ();
        goto done;
    }

#if 0
    memset (locos, 0, sizeof(locos));
    locoDisp ();
#endif

    for (int n = 0; N_LOCO > n; n++, p++)  {
        if (1 != fread ((void*) p, sizeof(Loco_t), 1, fp))  {
            printf (" %s: fread %d incomplete\n", __func__, n);
            break;
        }
    }

done:
    fclose (fp);
    locoDisp ();
}
