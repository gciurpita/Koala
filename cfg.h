#ifndef CFG_H
# define CFG_H

# include "vars.h"

// -----------------------------------------------------------------------------
#define WHYTE_LEN   10
#define LOCO_LEN    20

struct Engine_s {
    float  drvrDia;
    float  cylDia;
    float  cylStr;
    int    numCyl;

    int    PSI;
    int    wtAdh;
    int    wtTot;
    int    wtTndr;

    float  Grate;       // unused
    float  BlrLen;      // unused
    float  BlrDia;      // unused
    float  BlrVol;      // unused

    float  pipe;
        
    char   whyte [WHYTE_LEN];
    char   name  [LOCO_LEN];
};

// -------------------------------------
struct Loco_s {
    int     adr;
    float   mphToDcc;
    char    engine [LOCO_LEN];
};

// -------------------------------------
#define N_LOCO      20
#define N_ENGINE    20

struct Cfg_s {
    char     ssid [MAX_CHAR];
    char     pass [MAX_CHAR];

    char     host [MAX_CHAR];
    int      port;

    char     name [MAX_CHAR];

    Loco_s   locos   [N_LOCO];
    Engine_s engines [N_ENGINE];
};

#define Loco  cfg.locos

// -----------------------------------------------------------------------------
extern Cfg_s cfg;

void cfgDisp (void);
void cfgLoad (void);
void cfgSave (void);

#endif
