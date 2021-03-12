#ifndef CFG_H
# define CFG_H


extern const char *cfgFname;

// -------------------------------------
void cfgClr  (void);
void cfgDisp (void);
void cfgEdit (void);
void cfgLoad (const char *filename);
void cfgSave (const char *filename);

#endif
