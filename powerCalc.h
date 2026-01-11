#ifndef POWERCALC_H_INCLUDED
#define POWERCALC_H_INCLUDED

#include "PowerRing.h"

#define maxPower    6000
#define powerPerLed (maxPower/NUM_RING1)

extern volatile double powerGrid,powerBatterie,powerSolar,batterieStatus,helligkeitAussen;

void calcLedsFromPower(void);
void calcBatterieStatus(void);

#endif // POWERCALC_H_INCLUDED
