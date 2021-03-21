#include "powerCalc.h"

#define BRIGHTNESS 6

volatile double powerGrid=3000,powerBatterie=650,powerSolar=4500;
uint8_t powerLeds[NUMLEDS];

void calcLedsFromPower(void)
{
uint8_t posMarker=0,negMarker=NUMLEDS;
int8_t temp;
  fill_led_color(F_BLACK,BRIGHTNESS);
  temp = round(powerGrid/(powerPerLed));
  if(temp>0)
  {
    bar_led_color(F_GRUEN,BRIGHTNESS,posMarker,posMarker+temp);
    posMarker += temp;
  }
  else
  {
    bar_led_color(F_ROT,BRIGHTNESS,negMarker+temp,negMarker);  // temp ist negativ !!!
    negMarker += temp;
  }
  temp = round(powerBatterie/powerPerLed);
  if(temp>0)
  {
    bar_led_color(F_TUERKIS,BRIGHTNESS,posMarker,posMarker+temp);
    posMarker += temp;
  }
  else
  {
    bar_led_color(F_BLAU,BRIGHTNESS,negMarker+temp,negMarker);  // temp ist negativ !!!
    negMarker += temp;
  }
  temp = round(powerSolar/powerPerLed);
  if(temp>0)
  {
    bar_led_color(F_GELB,BRIGHTNESS,posMarker,temp);
  }
}
