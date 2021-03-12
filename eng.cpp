// getLoco simulates retrieving a loco description by loco name

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "eng.h"
// #include "koala.h"

Eng_s engs [N_ENG] = {
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

// -----------------------------------------------
void
engDisp (
    Eng_s   *p)
{
    if (0 == p->drvrDia)  {
        printf ("\n");
        return;
    }

    printf (" %5.1f", p->drvrDia);
    printf (" %5.1f", p->cylDia);
    printf (" %5.1f", p->cylStr);

    printf (" %2d",  p->numCyl);

    printf (" %3d",  p->PSI);
    printf (" %3d",  p->wtAdh);
    printf (" %3d",  p->wtTot);
    printf (" %3d",  p->wtTndr);

    printf (" %5.1f", p->grate);
    printf (" %5.1f", p->blrLen);
    printf (" %5.1f", p->blrDia);
    printf (" %5.1f", p->blrVol);

    printf (" %5.1f", p->pipeDia);

    printf (" %-10s", p->whyte);
    printf (" %s",    p->name);
    printf ("\n");
}
 
// -----------------------------------------------
char
engEdit (
    Eng_s       *p,
    const char  *desc )
{
    char s [100];
    do  {
        printf ("  %8s:", desc);
        engDisp (p);
        gets (s);

        sscanf (s, "%f %f %f %d %d %d %d %d %f %f %f %f %f %s %s",
            &p->drvrDia, &p->cylDia, &p->cylStr,  &p->numCyl, &p->PSI, 
            &p->wtAdh,   &p->wtTot,  &p->wtTndr,  &p->grate,  &p->blrLen, 
            &p->blrDia,  &p->blrVol, &p->pipeDia,  p->whyte,   p->name );
    } while (strlen (s) && 'q' != s[0]);

    return s [0];
}
 
// -----------------------------------------------
Eng_s *
engGet (
    char* name)
{
    Eng_s   *p = engs;

    for (unsigned n = 0; n < N_ENG; n++, p++)  {
        if (! strcmp(p->name, name))  {
            if (0 == p->blrVol)  {
                p->blrVol = p->blrLen *
                        M_PI * (p->blrDia / 24) * (p->blrDia / 24);
            }

            return p;
        }
    }

    printf ("%s: ERROR - %s unknown\n", __func__, name);
    return NULL;
}
