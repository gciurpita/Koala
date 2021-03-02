#ifndef VARS_H
# define VARS_H

#include <Arduino.h>    // needed for byte

#define MAX_CHAR  33

#define MAX_BRK   5
#define MAX_THR   100
#define MAX_REV   100
#define MAX_MID   (MAX_REV / 2)

enum {
    DIR_NEUTRAL = 0,
    DIR_FOR     = 1,
    DIR_REV     = -1
};

enum { V_NUL, V_STR, V_INT };

struct Vars_s {
    int        *p;
    const char *desc;
};

extern Vars_s  *pVars;

typedef struct {
    void       *p;
    byte        nByte;
    byte        type;
    const char *desc;
} EeVar_t;

extern EeVar_t *pEeVars;

// -------------------------------------
// dynamic variables

extern int      brakeInd;
extern float    brakeIndPct;
extern int      brakeCfm;

extern int      brakeAir;
extern float    brakeAirPct;
extern int      button;

extern int      cars;
extern int      carLen;

extern int      dir;

extern int      encApos;
extern int      encBpos;

extern int      grX10;

extern int      engine;
extern int      loco;

extern unsigned long    msec;
extern int      mass;
extern float    mph;
extern int      reverser;

extern int      slope;
extern int      state;

extern int      throttle;
extern int      timeSec;
extern int      tonnage;

extern int      tractEff;
extern int      tractEffMax;

extern int      whistle;
extern int      wtCar;
extern int      wtLoco;

// -------------------------------------
// stored variables
#define MAX_ADR  10
extern int      adr [MAX_ADR];

extern char     host [];
extern int      port;

extern char     ssid [];
extern char     pass [];
extern char     name [];

extern const char *version;

#endif
