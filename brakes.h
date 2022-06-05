#ifndef BRAKING_H
# define BRAKING_H

enum {
    BRK_A_REL,
    BRK_A_RUN,
    BRK_A_LAP,
    BRK_A_SVC1,
    BRK_A_SVC2,
    BRK_A_SVC3,
    BRK_A_EMER,
    BRK_A_LAST = BRK_A_EMER
};

enum {
    BRK_I_REL_QUICK,
    BRK_I_REL_SLOW,
    BRK_I_LAP,
    BRK_I_APP_SLOW,
    BRK_I_APP_QUICK,
    BRK_I_LAST = BRK_I_APP_QUICK
};

extern const char * airBrkStr [];
extern const char * indBrkStr [];

extern const char * brakeStr [];

extern float brkLnPsi;

extern void brakes   (int dMsec);
extern void brakesPr (int hdr);
extern void brakesMdlPr (void);

#endif
