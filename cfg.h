#ifndef CFG_H
# define CFG_H

# include <Arduino.h>

extern const char *cfgFname;

// -------------------------------------
void cfgClr  (void);
void cfgDisp (Stream &);
void cfgEdit (Stream &);
int  cfgLoad (const char *filename);
void cfgSave (const char *filename);

#endif