
#include "Arduino.h"

#include "koala.h"
#include "sound.h"

#if 0
static unsigned _funcChuff [2] = { 5, 6 };      // BLI
#else
static unsigned _funcChuff [2] = { 6, 5 };      // tsunami
#endif

// -----------------------------------------------------------------------------
void
soundInit (void)
{
}

// -----------------------------------------------------------------------------
int nChuffLevel = 6;
int chuffLevel;

void
soundChuff (
    int te,
    int teMax )
{
    int level = nChuffLevel * te / teMax;

    if (chuffLevel < level)  {
        chuffLevel ++;
        jmriFuncBut (_funcChuff [0]);
    }

    else if (chuffLevel > level)  {
        chuffLevel --;
        jmriFuncBut (_funcChuff [1]);
    }
}
