#ifndef LOCOS_H
# define LOCOS_H

typedef struct  {
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
        
    char   whyte [10];
    char   name  [20];
} Loco_t;

Loco_t * getLoco (char* name);

#endif
