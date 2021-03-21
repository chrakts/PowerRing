#include "powerCalc.h"

#define BRIGHTNESS 12

volatile double powerGrid=3000,powerBatterie=650,powerSolar=4500;
uint8_t powerLeds[NUMLEDS];

void calcLedsFromPower(void)
{
uint8_t posMarker=0;
int8_t temp,negMarker=NUMLEDS;
double eigenVerbrauch;
  fill_led_color(F_BLACK,BRIGHTNESS);
  eigenVerbrauch = powerSolar;
  if(powerBatterie>0)
    eigenVerbrauch-=powerBatterie;
  if(powerGrid>0)
    eigenVerbrauch-=powerGrid;

  temp = round(eigenVerbrauch/powerPerLed);
  if(temp>0)
  {
    bar_led_color(F_MAGENTA,BRIGHTNESS,posMarker,temp);
    posMarker += temp;
  }

  temp = round(powerBatterie/powerPerLed);
  if(temp>0)
  {
    bar_led_color(F_TUERKIS,BRIGHTNESS,posMarker,posMarker+temp);
    posMarker += temp;
  }
  else
  {
    bar_led_color(F_LILA,BRIGHTNESS,negMarker+temp,negMarker);  // temp ist negativ !!!
    negMarker += temp;
  }

  temp = round(powerGrid/(powerPerLed));
  if(temp>0)
  {
    bar_led_color(F_GRUEN,BRIGHTNESS,posMarker,posMarker+temp);
    posMarker += temp;
  }
  else
  {
    if(negMarker+temp<0)
      bar_led_color(F_ROT,BRIGHTNESS,0,negMarker);  // temp ist negativ !!!
    else
      bar_led_color(F_ROT,BRIGHTNESS,negMarker+temp,negMarker);  // temp ist negativ !!!
  }

}
