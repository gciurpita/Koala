 believ/// brakes implementation

#ifdef  Sim
# include <stdio.h>
# define PI          3.1412

#else
# include <Arduino.h>
#endif

#include "brakes.h"
#include "encoder.h"
#include "koala.h"
#include "vars.h"

// ---------------------------------------------------------
const char * brakeStr [] = {
    "REL",
    "RUN",
    "LAP",
    "SVC1",
    "SVC2",
    "SVC3",
    "EMER",
    "E-STOP"
};

// ---------------------------------------------------------
// determine brake position

#if 0
int stepsPerDetent = 2;
#else
int stepsPerDetent = 1;
#endif

int encAmin    = 0;
int encAmax    = BRK_LAST * stepsPerDetent;
int encAposLst = 0;

int encBmin    = 0;
int encBmax    = BRK_LAST * stepsPerDetent;
int encBposLst = 0;

static int _brakeUpdate (
    int   encPos,
    int & encPosLst,
    int & encMin,
    int & encMax )
{
    if (encMin > encPos)  {
        encMin = encPos;
        encMax = encPos + BRK_LAST * stepsPerDetent;
    }
    else if (encMax < encPos)  {
        encMax = encPos;
        encMin = encPos - BRK_LAST * stepsPerDetent;
    }

    encPosLst = encPos;

    return (encPos - encMin) / stepsPerDetent;
}

// -----------------------------------------------
static void _brakesUpdate ()
{
    if (encBposLst != encBpos)  {
        brake = _brakeUpdate (encBpos, encBposLst, encBmin, encBmax);
     // printf ("%s: %d %s\n", __func__, brake, brakeStr [brake]);
    }
}

// ---------------------------------------------------------
//
typedef struct {
    float rateRel;      // cu.ft. / min
    float rateSvc1;
    float rateSvc2;
    float rateSvc3;
    float rateEmer;
    
    int   dropSvc1;
    int   dropSvc2;

    const char* desc;
} Model_t;

Model_t models [] = {
    { 0.67, -0.85, -0.95, -1.05, -1.5, 10, 20, "self-lapping" },
    { 0.60, -0.85, -0.95, -1.05, -1.5,  0,  0, "non-self-lapping" },
};
#define N_MODELS    (sizeof(models)/sizeof(Model_t))

Model_t *pMdl = & models [0];

// ---------------------------------------------------------
// train brakes
#define AtmPsi      14.7
#define BrkPsiMax   90
#define SqFt        144

#define BrkLnDia    1.5
#define BrkLnRad    (BrkLnDia/2)
#define BrkLnArea   (PI * BrkLnRad * BrkLnRad)
#define BrkPctCoef    3

#define BrkRsvrVol  1.5

float brkLnPsi    = 0;
float brkLnPsi_0  = 0;
float brkLnPsiLst = 0;
float brkLnPsiMin = 0;

float brkLnFil    = 0;
float brkRsvrFil  = 0;
float brkTotFil   = 0;

float brkFlRat    = 0;

float brkLnVol;
float brkRsvrVol;

float timeMsec    = 0;

void _trainBrakes (
    int dMsec )
{ 
    timeMsec += dMsec;

    _brakesUpdate ();

    brkFlRat    = 0;
    brkLnPsiLst = brkLnPsi;

    switch (brake)  {
    case BRK_ESTOP:
        brakePct = brkLnFil = brkLnPsi = 0;
        eStop ();
        return;

    case BRK_REL:
        brkFlRat   = pMdl->rateRel;
        brkLnPsi_0 = brkLnPsi;
        break;

    case BRK_SVC3:
        brkLnPsiMin = 0;
        brkFlRat    = pMdl->rateSvc3;
        break;

    case BRK_SVC2:
        brkLnPsiMin = pMdl->dropSvc1 ? brkLnPsi_0 - pMdl->dropSvc2 : 0;
        brkFlRat    = pMdl->rateSvc2;
        break;

    case BRK_SVC1:
        brkLnPsiMin = pMdl->dropSvc1 ? brkLnPsi_0 - pMdl->dropSvc1 : 0;
        brkFlRat    = pMdl->rateSvc1;
        break;

    case BRK_EMER:
        brkLnPsiMin = 0;
        brkFlRat    = pMdl->rateEmer;
        break;

    case BRK_RUN:
    case BRK_LAP:
    default:
        brkFlRat    = 0;
        break;
    }

    // -----------------------------------------------
    // update brake line and reservoir fill
    brkLnVol   = cars * carLen * BrkLnArea / SqFt;
    brkRsvrVol = cars * BrkRsvrVol;


    // update brake line and reservoir fill
    if (0 > brkFlRat && brkLnPsiMin < brkLnPsi)  {  // dropping
        brkLnFil  = brkLnVol * brkLnPsi / AtmPsi;
        brkLnFil += brkFlRat * dMsec / 1000;        // filRate negative

        if (0 > brkLnFil)
            brkLnFil = 0;
    }
    // need to fill air in both line and reservoir
    else if (0 < brkFlRat && brkLnPsi < BrkPsiMax)  {   // filling
        brkTotFil  = (brkRsvrFil + brkLnVol) * brkLnPsi / AtmPsi;
        brkTotFil += brkFlRat * dMsec / 1000;
        brkLnFil   = brkLnVol * brkTotFil / (brkRsvrFil + brkLnVol);

        if (0 > brkLnFil)
            brkLnFil = 0;
    }

    // update brake line pressure
    if (0 == brkLnVol)
        brkLnPsi  = 0;
    else
        brkLnPsi  = AtmPsi * brkLnFil / brkLnVol;

    // min/max limits 
    if (brkLnPsi < brkLnPsiMin)
        brkLnPsi = brkLnPsiMin;
    if (BrkPsiMax < brkLnPsi)
        brkLnPsi = BrkPsiMax;

    // update braking %
    float dBrkLnPsi = brkLnPsi_0 - brkLnPsi;
    if (0 < dBrkLnPsi)  {
        brakePct = BrkPctCoef * dBrkLnPsi;
        brakePct = 100 < brakePct ? 100 : brakePct;
    }

    else if (brkLnPsi > brkLnPsiLst)
        brakePct = 0;
}

// ---------------------------------------------------------
// independent brake routine


// ---------------------------------------------------------
void
#ifdef Sim
brakesPr (
    int  hdr)
{
    if (hdr)  {
        printf ("\n");
        printf (" %4s", "Pos");
        printf (" %4s", "Vol");
        printf (" %6s", "Rate");
        printf (" %6s", "Fil");
        printf (" %6s", "PSI");
        printf (" %5s", "Pct");

        printf (" %4s", "Car");
        printf (" %6s", "Time");
        printf ("\n");
    }
#else
brakesPr (void)
{
#endif

    printf (" %4s",   brakeStr [brake]);
    printf (" %4.1f", brkLnVol);
    printf (" %6.2f", brkFlRat);
    printf (" %6.1f", brkLnFil);
    printf (" %6.1f", brkLnPsi);
    printf (" %3d %%", brakePct);

#ifdef Sim
 // printf (" %6.1f", brkLnPsi_0);
    printf (" %4d",   cars);
    printf (" %6.1f", timeMsec / 1000);
#endif
}

// ---------------------------------------------------------
void
brakes (
    int dMsec )
{
    _trainBrakes (dMsec);
}
