
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

