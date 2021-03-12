#ifndef LOCOS_H
# define LOCOS_H

#define WHYTE_LEN   10
#define LOCO_LEN    20

#define N_ENG       20

struct Eng_s {
    float  drvrDia;
    float  cylDia;
    float  cylStr;
    int    numCyl;

    int    PSI;
    int    wtAdh;
    int    wtTot;
    int    wtTndr;

    float  grate;       // unused
    float  blrLen;      // unused
    float  blrDia;      // unused
    float  blrVol;      // unused

    float  pipeDia;
        
    char   whyte [WHYTE_LEN];
    char   name  [LOCO_LEN];
};

// -------------------------------------
extern Eng_s engs [];

// -----------------------------------------------
void    engDisp (Eng_s *p);
char    engEdit (Eng_s *p, const char *desc);
Eng_s * getEng  (char* name);

#endif
