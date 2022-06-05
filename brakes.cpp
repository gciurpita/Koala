// air & independent brakes implementation

#ifdef  Sim
# include <stdio.h>
#endif

#include "brakes.h"
#include "encoder.h"
#include "vars.h"

// ---------------------------------------------------------
const char * airBrkStr [] = {
    "REL",
    "RUN",
    "LAP",
    "SVC1",
    "SVC2",
    "SVC3",
    "EMER",
    "ovrFlw",
};

// terms from 1946 Victoria Railways Air Brakes pg 72
const char * indBrkStr [] = {
    "RE-Q",
    "RE-S",
    "LAP",
    "AP-S",
    "AP-Q",
    "ovrFlw",
};

// ---------------------------------------------------------
// determine brake position

#if 1
int stepsPdetent = 2;
#else
int stepsPdetent = 1;
#endif

typedef struct {
    int     nSteps;
    int     max;
    int     min;
    int     pos;
    int     posLst;
} Enc;

static Enc _encAir = { BRK_A_LAST * stepsPdetent, BRK_A_LAST * stepsPdetent };
static Enc _encInd = { BRK_I_LAST * stepsPdetent, BRK_I_LAST * stepsPdetent };

static int _brakeUpdate (
    int   encPos,
    Enc  *p )
{
    if (p->min > encPos)  {
        p->min = encPos;
        p->max = encPos + p->nSteps;
    }
    else if (p->max < encPos)  {
        p->max = encPos;
        p->min = encPos - p->nSteps;
    }

    p->posLst = encPos;

    return (encPos - p->min) / stepsPdetent;
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
    {  100,   -85,   -95,  -105, -150, 10, 20, "self-lapping" },
    {  100,   -85,   -95,  -105, -150,  0,  0, "non-self-lapping" },
    {   89,   -30,   -53,  -105, -300,  0,  0, "Mark Values" },
};
#define N_MODELS    (sizeof(models)/sizeof(Model_t))

Model_t *pMdl = & models [2];

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

float brkLnPsi;
float brkLnPsi_0  = 0;
float brkLnPsiLst = 0;
float brkLnPsiMin = 0;

float brkLnFil    = 6;          // gross estimate
// float brkRsvrFil  = 0;      // ??? brkRsvrVol ?
float brkTotFil   = 0;

float brkFlRat    = 0;

float brkLnVol;
float brkRsvrVol;

float timeMsec    = 0;

void _airBrakes (
    int dMsec )
{
    if (0)
        printf ("%s: brkLnPsi %4.1f, brakeAir %d\n",
            __func__, brkLnPsi, brakeAir);

    float perMin = dMsec / 60000.0;

    brakeAir = _brakeUpdate (encBpos, & _encAir);

    brkFlRat    = 0;
    brkLnPsiLst = brkLnPsi;

    switch (brakeAir)  {
    case BRK_A_REL:
    case BRK_A_RUN:
        brkFlRat   = pMdl->rateRel * perMin;
        brkLnPsi_0 = brkLnPsi;
        break;

    case BRK_A_SVC3:
        brkLnPsiMin = 0;
        brkFlRat    = pMdl->rateSvc3 * perMin;
        break;

    case BRK_A_SVC2:
        brkLnPsiMin = pMdl->dropSvc1 ? brkLnPsi_0 - pMdl->dropSvc2 : 0;
        brkFlRat    = pMdl->rateSvc2 * perMin;
        break;

    case BRK_A_SVC1:
        brkLnPsiMin = pMdl->dropSvc1 ? brkLnPsi_0 - pMdl->dropSvc1 : 0;
        brkFlRat    = pMdl->rateSvc1 * perMin;
        break;

    case BRK_A_EMER:
        brkLnPsiMin = 0;
        brkFlRat    = pMdl->rateEmer * perMin;
        break;

    case BRK_A_LAP:
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
        if (0) printf (" %s: brkFlRat %4.1f\n", __func__, brkFlRat);
    }
    // need to fill air in both line and reservoir
    else if (0 < brkFlRat && brkLnPsi < BrkPsiMax)  {   // filling
        brkTotFil  = (brkRsvrVol + brkLnVol) * brkLnPsi / AtmPsi;
        brkTotFil += brkFlRat * dMsec / 1000;
        brkLnFil   = brkLnVol * brkTotFil / (brkRsvrVol + brkLnVol);

        if (0 > brkLnFil)
            brkLnFil = 0;
        if (0) printf (" %s: brkFlRat %4.1f\n", __func__, brkFlRat);
    }

    // update brake line pressure
    if (0 == brkLnVol)
        brkLnPsi  = 0;
    else
        brkLnPsi  = AtmPsi * brkLnFil / brkLnVol;

    if (0)
        printf (" %s: brkLnPsi %4.1f, brkLnVol %.1f, brkLnFil %.1f\n",
            __func__, brkLnPsi, brkLnVol, brkLnFil);

    // min/max limits
    if (brkLnPsi < brkLnPsiMin)
        brkLnPsi = brkLnPsiMin;

    if (BrkPsiMax < brkLnPsi)       // brkLnTotFil
        brkLnPsi = BrkPsiMax;

    // update braking %
    float dBrkLnPsi = brkLnPsi_0 - brkLnPsi;
    if (0 < dBrkLnPsi)  {
        brakeAirPct = BrkPctCoef * dBrkLnPsi;
        brakeAirPct = 100 < brakeAirPct ? 100 : brakeAirPct;
    }

    else if (brkLnPsi > brkLnPsiLst)
        brakeAirPct = 0;
}

// ---------------------------------------------------------
//
typedef struct {
    float relQuick;     // % per second
    float relSlow;
    float lap;
    float appSlow;
    float appQuick;

    const char* desc;
} ModelInd_t;

ModelInd_t modelInd [] = {
    { -100.0/5, -100/15,  0.0, 100.0/15, 100.0/5, "ind model 1" },
};
#define N_MODEL_IND    (sizeof(modelInd)/sizeof(ModelInd_t))

ModelInd_t *pMdlInd = & modelInd [0];


// ---------------------------------------------------------
// independent brake routine

void _indBrakes (
    int dMsec )
{
    float perSec = dMsec / 1000.0;

    brakeInd = _brakeUpdate (encApos, & _encInd);

    switch (brakeInd)  {
    case BRK_I_REL_QUICK:
        brakeIndPct += pMdlInd->relQuick * perSec;
        break;

    case BRK_I_REL_SLOW:
        brakeIndPct += pMdlInd->relSlow * perSec;
        break;

    case BRK_I_APP_SLOW:
        brakeIndPct += pMdlInd->appSlow * perSec;
        break;

    case BRK_I_APP_QUICK:
        brakeIndPct += pMdlInd->appQuick * perSec;
        break;

    default:
        break;
    }

#define BRK_IND_MAX     100
#define BRK_IND_MIN       0

    // limit
    if (BRK_IND_MAX < brakeIndPct)
        brakeIndPct = BRK_IND_MAX;

    if (BRK_IND_MIN > brakeIndPct)
        brakeIndPct = BRK_IND_MIN;
}

// ---------------------------------------------------------
void
brakesMdlPr (void)
{
    printf ("%s:", __func__);
    printf (" %.1f Rel",  pMdl->rateRel);
    printf (" %.1f Svc1", pMdl->rateSvc1);
    printf (" %.1f Svc2", pMdl->rateSvc2);
    printf (" %.1f Svc3", pMdl->rateSvc3);
    printf (" %.1f Emer", pMdl->rateEmer);
    printf ("\n");
}

// ---------------------------------------------------------
void
brakesPr (
    int  hdr)
{
    if (hdr)
    {
        printf (" %4s", "Pos");
        printf (" %4s", "vol");
        printf (" %6s", "flRat");
        printf (" %6s", "fil");
        printf (" %6s", "psi");
        printf (" %5s", "pct");
        printf (" %9s", "Independent");
        return;
    }

    printf (" %4s",   airBrkStr [brakeAir]);
    printf (" %4.1f", brkLnVol);
    printf (" %6.2f", brkFlRat);
    printf (" %6.1f", brkLnFil);
    printf (" %6.1f", brkLnPsi);
    printf (" %3.0f %%", brakeAirPct);

    printf (" %5s",   indBrkStr [brakeInd]);
    printf (" %3.0f %%", brakeIndPct);
}

// ---------------------------------------------------------
void
brakes (
    int dMsec )
{
    timeMsec += dMsec;

    _airBrakes (dMsec);
    _indBrakes (dMsec);
}
