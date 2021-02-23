
#include <Arduino.h>

#include "pins.h"
#include "pots.h"
#include "vars.h"

#define ADC_MAX   4095

// -----------------------------------------------------------------------------
void
potsRead (void)
{
    slope    = 100 * analogRead (ADC_SLOPE)   / ADC_MAX;
    whistle  = 100 * analogRead (ADC_WHISTLE) / ADC_MAX;
    reverser = 100 * analogRead (ADC_REV)     / ADC_MAX;
    throttle = 100 * analogRead (ADC_THR)     / ADC_MAX;
}

