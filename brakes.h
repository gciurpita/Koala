#ifndef BRAKING_H
# define BRAKING_H

enum {
    BRK_REL,
    BRK_RUN,
    BRK_LAP,
    BRK_SVC1,
    BRK_SVC2,
    BRK_SVC3,
    BRK_EMER,
    BRK_ESTOP,
    BRK_LAST
};

extern const char * brakeStr [];

extern void brakes   (int dMsec);
extern void brakesPr (void);

#endif
