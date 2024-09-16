
#include "Arduino.h"

#include "koala.h"
#include "sound.h"

#if 0
static unsigned _funcChuff [2] = { 5, 6 };      // BLI
static unsigned _funcBrake [2] = { 28, 28 };    // BLI
#else
static unsigned _funcChuff [2] = { 6, 5 };      // tsunami
static unsigned _funcBrake [2] = { 314, 314 };  // tsunami
#endif

// -----------------------------------------------------------------------------
void
soundInit (void)
{
}

// -----------------------------------------------------------------------------
static byte _brakeSqueal;

void
soundBrkSql (
    float pct )
{
    if (0 < pct && ! _brakeSqueal)  {
        _brakeSqueal = ! _brakeSqueal;
        jmriFuncKey (_funcBrake [1], FUNC_SET);
    }
    else if (0 == pct && _brakeSqueal)  {
        _brakeSqueal = ! _brakeSqueal;
        jmriFuncKey (_funcBrake [1], FUNC_CLR);
    }
}
// -----------------------------------------------------------------------------
static byte _nChuffLevel = 6;
static byte _chuffLevel;

void
soundChuff (
    int te,
    int teMax )
{
    int level = _nChuffLevel * te / teMax;

    if (_chuffLevel < level)  {
        _chuffLevel ++;
        jmriFuncBut (_funcChuff [0]);
    }

    else if (_chuffLevel > level)  {
        _chuffLevel --;
        jmriFuncBut (_funcChuff [1]);
    }
}
