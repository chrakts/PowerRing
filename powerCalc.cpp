#include "powerCalc.h"

#define BRIGHTNESS 12

#define MIN_BRIGHTNESS 4
#define MAX_BRIGHTNESS 80

volatile double powerGrid=-1200,powerBatterie=-300,powerSolar=1500,batterieStatus=50,helligkeitAussen=50;


void calcLedsFromPower(void)
{
uint8_t posMarker=0;
int8_t temp,negMarker=NUM_RING1;
double eigenVerbrauch;
uint8_t brightness;

 /* brightness = uint8_t(helligkeitAussen/10.0);
  if (brightness< MIN_BRIGHTNESS)
    brightness = MIN_BRIGHTNESS;
  if (brightness> MAX_BRIGHTNESS)
    brightness = MAX_BRIGHTNESS;*/

  //brightness = calcBrightness();
  brightness = get_led_autobright(helligkeitAussen);

  fill_led_color(F_BLACK,brightness);
  eigenVerbrauch = powerSolar;
  if(powerBatterie>0)
    eigenVerbrauch-=powerBatterie;
  if(powerGrid>0)
    eigenVerbrauch-=powerGrid;

  temp = round(eigenVerbrauch/powerPerLed);
  if(temp>0)
  {
    bar_ring1_color(F_MAGENTA,brightness,posMarker,temp);
    posMarker += temp;
  }

  temp = round(powerBatterie/powerPerLed);
  if(temp>0)
  {
    bar_ring1_color(F_TUERKIS,brightness,posMarker,posMarker+temp);
    posMarker += temp;
  }
  else
  {
    bar_ring1_color(F_LILA,brightness,negMarker+temp,negMarker);  // temp ist negativ !!!
    negMarker += temp;
  }

  temp = round(powerGrid/(powerPerLed));
  if(temp>0)
  {
    bar_ring1_color(F_GRUEN,brightness,posMarker,posMarker+temp);
    posMarker += temp;
  }
  else
  {
    if(negMarker+temp<0)
      bar_ring1_color(F_ROT,brightness,0,negMarker);  // temp ist negativ !!!
    else
      bar_ring1_color(F_ROT,brightness,negMarker+temp,negMarker);  // temp ist negativ !!!
  }

}

void calcBatterieStatus()
{
  int8_t temp;
  uint8_t brightness;
/*
  brightness = uint8_t(helligkeitAussen/10.0);
  if (brightness< MIN_BRIGHTNESS)
    brightness = MIN_BRIGHTNESS;
  if (brightness> MAX_BRIGHTNESS)
    brightness = MAX_BRIGHTNESS;
*/
  brightness = calcBrightness();
  temp = round(batterieStatus/4-1-1); // die ersten 4% werden nicht angezeigt -> Dadurch ergibt sich mit 24 LEDs: 4%/LED
  if(temp < 0)
    temp = 0;
  if(temp<7)
  {
    if(temp<4) // Rot
    {
      bar_ring2_color(F_ROT,brightness,0,temp+1);
    }
    else // Gelb
    {
      bar_ring2_color(F_GELB,brightness,0,temp+1);
    }
  }
  else // Grün
  {
    bar_ring2_color(F_GRUEN,brightness,0,temp+1);
  }
}

uint8_t calcBrightness()
{
uint8_t brightness;

  if( Nachtabschaltung == true)
  {
    brightness = 0;
  }
  else
  {
    brightness = uint8_t(helligkeitAussen/10.0);
    if (brightness< MIN_BRIGHTNESS)
      brightness = MIN_BRIGHTNESS;
    if (brightness> MAX_BRIGHTNESS)
      brightness = MAX_BRIGHTNESS;
  }
  return(brightness);
}
