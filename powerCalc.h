#ifndef POWERCALC_H_INCLUDED
#define POWERCALC_H_INCLUDED

#include "PowerRing.h"

#define maxPower    6000
#define powerPerLed (maxPower/NUMLEDS)

extern volatile double powerGrid,powerBatterie,powerSolar;

void calcLedsFromPower(void);

#endif // POWERCALC_H_INCLUDED
