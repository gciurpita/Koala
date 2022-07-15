// physics models

#define Sim
#ifdef  Sim
# include <stdio.h>
#else
# include <Arduino.h>
#endif

#include "brakes.h"
#include "engine.h"
#include "koala.h"
#include "phyConst.h"
#include "physics.h"
#include "rollRes.h"
#include "vars.h"

unsigned long msecLst = 0;
int           dMsec;

#define ABS(x)   (0 > (x) ? -(x) : (x))
#define SGN(x)   (0 > (x) ? -1   : 1)
#define NBR     0.10        // nominal brake ratio

// ---------------------------------------------------------
void _reverser (void)
{
    if (DIR_FOR != dir && (MAX_MID + 10) < reverser)  {
        dir = DIR_FOR;
        wifiSend ("TR1");
        printf (" %s: %3d For\n", __func__, reverser);
    }
    else if (DIR_REV != dir && (MAX_MID - 10) > reverser)  {
        dir = DIR_REV;
        wifiSend ("TR0");
        printf (" %s: %3d Rev\n", __func__, reverser);
    }
    else if (DIR_NEUTRAL != dir &&
        (MAX_MID - 10) < reverser && reverser < (MAX_MID + 10))  {
        dir      = DIR_NEUTRAL;
        printf (" %s: %3d Neutral\n", __func__, reverser);
    }
}

// ---------------------------------------------------------
void _throttle (void)
{
    tractEff = tractEffMax * throttle / MAX_THR;
}

// -----------------------------------------------------------------------------
#define G   32.2        // gravitation acceleration ft/sec/sec

float brkF;
float grF;              // grade
float acc;
float force;

int   a[10];
float fps = 0;          // should be initialized when loco set
int   b[10];

int   hdr = 0;
int   mphLst = 0;
float whRes;
int   wtTot;

int sec;
int mins;

// ---------------------------------------------------------
void
#if 0
disp (
    unsigned long msec,
    int           flag,
    int           brkMode )
#else
disp (void)
#endif
{
    static char constants = 0;

    if (! constants)  {
        constants++;
        printf ("%s: wtLoco %d, wtCar %d, wtTot %d, mass %d\n",
            __func__, pEng->wtLoco, wtCar, wtTot, mass);
        brakesMdlPr ();
    }

    mins  = msec / 60000;
    sec   = msec % 60000;

    if (! (hdr++ % 10))  {
        printf (" %7s", "time");
        printf (" %4s %3s %3s", "cars", "cut", "thr");
        printf (" %6s %7s %6s %6s", "drawBr", "res", "grF", "brF");
        printf (" %5s %6s %6s %4s", "force", "acc", "fps", "mph");

        if (DBG_BRAKE & debug)
            brakesPr (1);
        else if (DBG_ENGINE & debug)
            enginePr (1);
        printf ("\n");
    }

    // time
    printf (" %2d:%04.1f", mins, sec / 1000.0);

    printf (" %4d", cars);
    printf (" %s%2d", 0>dir ? "-" : " ", cutoff);
    printf (" %3d", throttle);

    printf (" %6d", tractEff);
    printf (10 > whRes      ? " %7.2f" : " %7.0f", whRes);
    printf (" %6.1f", grF);
    printf (10 > ABS(brkF)  ? " %6.2f" : " %6.0f", brkF);

    printf (10 > ABS(force) ? " %5.2f" : " %5.0f", force);
    printf (" %6.2f", acc);
    printf (10 > fps ? " %6.4f" : " %6.0f", fps);
    printf (10 > mph ? " %4.2f" : " %4.1f", mph);

    if (DBG_BRAKE & debug)
        brakesPr (0);
    else if (DBG_ENGINE & debug)
        enginePr (0);

    printf ("\n");
}

// ---------------------------------------------------------
void
physics (
unsigned long msec,
int           dispFlag,
int           brkMode )
{
    if (0)
        printf ("%s: %ld msec, flag %d, brkMode %d\n",
            __func__, msec, dispFlag, brkMode);

    dMsec   = msec - msecLst;
    msecLst = msec;
    if (dMsec > 1000)  {
        return;
    }

    _reverser ();
    brakes (dMsec);
#if 0
    _throttle ();
#else
    cutoff      = 1.6 * ABS(reverser-MAX_MID);
    tractEff    = engineTe (dMsec / 1000.0, fps, throttle, cutoff);
#endif

    tonnage = (cars * wtCar);
    wtTot   = (tonnage + pEng->wtLoco + pEng->wtTndr) * LbPton;

    // -------------------------------------
    // forces

    // tractive effort
    force      = tractEff;

    // grade relative to forward direction of train
    force     += grF = -wtTot * grX10 / 1000;

    // wheel resistance
    float rf   =  rollRes (fps/MphTfps);
    float tons =  wtTot / LbPton;
    whRes      = -SGN(mph) * rf * tons;
    if (0 != mph)
        force     += whRes;

    // brakes
    brkF  = (cars * wtCar) * brakeAirPct / 100;
    brkF +=  pEng->wtLoco  * brakeIndPct / 100;
    brkF *= -SGN(mph) * LbPton * NBR;

    // brake force shouldn't cause train to move
    //     can't excede tractive + grade force
    //     train resistance is zero when stopped
    if (0 == mph && ABS(brkF) >= ABS(force))
        force  = 0;
    else
        force += brkF;

#if 0
    printf (" %s: %6.4f %6.4f %6.4f %6.0f %6.4f %d\n",
        __func__, tractEff, whRes, grF, brkF, force, ABS(force) <= brkF);
#endif

    // -------------------------------------
    // acceleration (Newton's equation)
    mass  = wtTot / G;
    acc   = force / mass;
    fps  += acc * dMsec / 1000;
    mph   = fps / MphTfps;

    static float mphLst;
    if (0 != mphLst && SGN(mphLst) != SGN(mph))
        fps = mph = 0;
    mphLst = mph;

    // -------------------------------------
#if 1
    static unsigned long msecLst2 = 0;
    if (debug && ((msec - msecLst2) > 1000))  {
        msecLst2 = msec;
        disp ();
    }
#else
    if (debug)
        disp ();
#endif
}
