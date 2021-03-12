
#include "vars.h"

const char *version   = "210308";

int      brakeAir;
float    brakeAirPct;
int      brakeCfm;

int      brakeInd;
float    brakeIndPct;
int      button;

int      cars;
int      carLen  = 40;

int      dir;

int      encApos;
int      encBpos;

int      grX10;

int      engine;
int      loco;

unsigned long    msec;
int      mass;
float    mph;
int      reverser;

int      slope;
int      state;

int      throttle;
int      timeSec;
int      tonnage;

int      tractEff;
int      tractEffMax;

int      whistle;
int      wtCar;
int      wtLoco;


// -----------------------------------------------------------------------------
// list of vars to display

Vars_s vars [] = {
    { & brakeAir,    "brakeAir" },
 // { & brakeAirPct, "brakeAirPct" },
    { & brakeInd,    "brakeInd" },
 // { & brakeIndPct, "brakeIndPct" },
    { & brakeCfm,    "brakeCfm" },

    { & cars,     "cars" },
    { & carLen,   "carLen" },
    { & dir,      "dir" },
    { & loco,     "loco" },
 // { & mph,      "mph" },
    { & mass,     "mass" },
    { & reverser, "reverser" },
    { & state,    "state" },
    { & throttle, "throttle" },
    { & tractEff, "tractEff" },
    { & tractEffMax, "tractEffMax" },
    { & timeSec,  "timeSec" },
    { & tonnage,  "tonnage" },
    { & wtCar,    "wtCar" },
    { & wtLoco,   "wtLoco" },
    { 0,        NULL },
};

Vars_s *pVars = & vars [0];

// -----------------------------------------------------------------------------
//  stored variables

char     name [MAX_CHAR] = "Koala 4 Throttle";

// WiFi and JMRI Server Definitions
#if 1
char     ssid [MAX_CHAR] = "WiFi-ssid";
char     pass [MAX_CHAR] = "WiFi-password";

char     host [MAX_CHAR] = "192.168.1.100";
int      port            = 12080;

#else
char     ssid [MAX_CHAR] = "FiOS-DGHZ0";
char     pass [MAX_CHAR] = "panorama123";

char     host [MAX_CHAR] = "192.168.1.174";
int      port            = 12080;
#endif

Loco_s locos [N_LOCO] = {
    { 100, 1.2, "I-10sa"    },
    { 200, 1.2, "G-1sas"    },
    { 300, 1.2, "K-1"       },
    { 400, 1.2, "T-1"       },
    { 500, 1.2, "NA_2-6-2"  },
    { 600, 1.2, "BigBoy"    },
    { 700, 1.2, "catskill"  },
    { 800, 1.2, "MILW_4-4-2"},
    { 900, 1.2, "MILW_F-6"  },
};

