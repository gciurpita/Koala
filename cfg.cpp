// define memory for configuration variables and
// statically defines default values
//
#include <Arduino.h>
#include "cfg.h"

Cfg_s cfg = {
     "WiFi-ssid",
     "WiFi-password",

     "192.168.1.100",
     12080,

     "Koala 4 Throttle",

     {
        { 100, 1.2, "I-10sa"    },
        { 200, 1.2, "G-1sas"    },
        { 300, 1.2, "K-1"       },
        { 400, 1.2, "T-1"       },
        { 500, 1.2, "NA_2-6-2"  },
        { 600, 1.2, "BigBoy"    },
        { 700, 1.2, "catskill"  },
        { 800, 1.2, "MILW_4-4-2"},
        { 900, 1.2, "MILW_F-6"  },
     },

     {
       //  drvr    cyl-size   #   PSI   Adh   Tot   Tnd  Grate  BlrLn  BlrDi  BlrVol Pipe  Whyte      Name 
        {  61.5, 27.0, 32.0,  2,  220,  132,  146,   90,  95.0,  13.5,  88.0,      0, 0.0, "2-8-0",   "I-10sa"    },
        {  80.0, 25.0, 28.0,  2,  200,   90,  140,   90,  95.0,  19.0,  80.0,      0, 0.0, "4-6-2",   "G-1sas"    },
        {  61.5, 30.5, 32.0,  2,  220,  160,  200,  115, 108.0,  22.2, 100.0,      0, 0.0, "2-10-2",  "K-1"       },
        {  70.0, 27.0, 32.0,  2,  240,  126,  200,   90,  95.0,  13.5,  88.0,      0, 0.0, "4-8-4",   "T-1"       },
        {  36.0, 13.0, 18.0,  2,  180,   24,   34,    0,   9.0,  11.0,  40.0,      0, 8.0, "2-6-2T",  "NA_2-6-2"  },
        {  68.0, 23.8, 32.0,  4,  300,  270,  380,  170, 150.0,  18.0,  95.0,      0, 0.0, "4-8-8-4", "BigBoy"    },
        {  84.0, 19.0, 28.0,  2,  300,   74,  140,  123,  69.0,  19.0,  80.0,      0, 0.0, "4-4-2",   "MILW_4-4-2"},
        {  80.0, 26.0, 28.0,  2,  225,   86,  187,  138,  80.0,  19.0,  80.0,      0, 0.0, "F-6",     "MILW_F-6"  },
        {  84.0, 23.5, 30.0,  2,  300,  108,  207,  187,  96.5,  19.0,  82.5,      0, 0.0, "F-7",     "MILW_F-7"  },
        {  70.0, 27.0, 32.0,  2,  320,  160,  247,  189, 107.7,   0.0,   0.0,      0, 0.0, "4-8-4",   "N&W"       },
    }
};

// ---------------------------------------------------------
void
cfgDisp (void)
{
    printf ("%s:\n", __func__);
    printf ("    %20s ssid\n", cfg.ssid);
    printf ("    %20s pass\n", cfg.pass);
    printf ("    %20s host\n", cfg.host);
    printf ("    %20d port\n", cfg.port);
    printf ("    %20s name\n", cfg.name);
    printf ("\n");

    for (unsigned n = 0; n < 10; n++)
        printf ("    %6d %4.1f %s\n",
            cfg.locos [n].adr, cfg.locos [n].mphToDcc, cfg.locos [n].engine);
    printf ("\n");

    for (unsigned n = 0; n < 12; n++)
        printf ("    %4.1f %-10s  %s\n",
        cfg.engines [n].drvrDia, cfg.engines [n].whyte, cfg.engines [n].name);
    printf ("\n");
}

// ---------------------------------------------------------
const char *cfgFname = "koala.dat";

void
cfgLoad (void)
{
    FILE  *fp;

    if (NULL == (fp = fopen (cfgFname, "rb+")))  {
        perror ("cfgLoad fopen");
        return;
    }

    if (! fread ((void*) &cfg, sizeof(cfg), 1, fp))  {
        perror ("cfgLoad fwrite");
    }

    fclose (fp);
}

// ---------------------------------------------------------
void
cfgSave (void)
{
    FILE  *fp;

    if (NULL == (fp = fopen (cfgFname, "ab+")))  {
        perror ("cfgSave fopen");
        return;
    }

    rewind (fp);
    if (! fwrite ((void*) &cfg, sizeof(cfg), 1, fp))  {
        perror ("cfgSave fwrite");
    }

    fclose (fp);
}
