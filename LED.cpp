/*
 * LED.cpp
 *
 * Created: 13.02.2016 12:25:00
 *  Author: Christof
 */

#include "PowerRing.h"
#include "gammacorrection.h"
#include "LED.h"
#include "ws2812.h"

static const uint8_t PROGMEM GammaTable[] = GCN_TABLE7TO8; // Original ! 128 Bytes
//static const uint8_t GammaTable[] = GCN_TABLE7TO8;

FARBE leds[NUMLEDS] = {F_ROT,F_LILA} ;  // 72 Bytes

// uint16_t AutoGain[20]= {0,0,0,10,15,20,40,80,160,320,640,1280,2560,5120,10240,20480,2560,30960,35960,40960};
uint16_t AutoGain[20]= {0,0,100,200,300,350,400,500,600,700,800,900,1000,2000,65535,65535,65535,65535,65535};



uint8_t get_led_autobright(uint16_t lumi)
{
  if( Nachtabschaltung == true)
  {
    return(0);
  }
  else
  {
    int i=19;
    while( (lumi<AutoGain[i]) & (i!=0) )
      i--;
    if(i>15)
      i=15;
    if(i<3)
      i=3;
    return(i);
  }
}



uint8_t ring1(uint8_t index)
{
  #define ring1Start 24
  #define ring1Offset 11
  #define ring1Number 24
  #define ring1Direction -1
  int8_t temp=0;
  temp = index * ring1Direction + ring1Offset;
  if(temp < 0)
    temp += ring1Number;
  temp = temp % ring1Number;
  return( uint8_t(temp)+ring1Start );
}

uint8_t ring2(uint8_t index)
{
  #define ring2Start  0
  #define ring2Offset -1
  #define ring2Number 24
  #define ring2Direction 1
  int8_t temp=0;
  temp = index * ring2Direction + ring2Offset;
  if(temp < 0)
    temp += ring2Number;
  temp = temp % ring2Number;
  return(uint8_t(temp)+ring2Start);
}

void set_led_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright,uint8_t index)
{
	if (index<NUMLEDS)
	{
		leds[index].rot = r;
		leds[index].gruen = g;
		leds[index].blau = b;

		if (bright!=BR_NOCHANGE)
		{
			leds[index].brightness = bright;
		}
	}
}

void bar_led_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright,uint8_t start, uint8_t ende)
{
  for(uint8_t i=start;i<ende;i++)
  {
    set_led_color(r,g,b,bright,i);
  }
}

void bar_ring1_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright,uint8_t start, uint8_t ende)
{
  for(uint8_t i=start;i<ende;i++)
  {
    set_led_color(r,g,b,bright,ring1(i));
  }
}

void bar_ring2_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright,uint8_t start, uint8_t ende)
{
  for(uint8_t i=start;i<ende;i++)
  {
    set_led_color(r,g,b,bright,ring2(i));
  }
}

void fill_led_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright)
{
	uint8_t i;

	for (i=0;i<NUMLEDS;i++)
	{
    set_led_color(r,g,b,bright,i);
	}
}

void fill_led_brightness(uint8_t bright)
{
	uint8_t i;

	for (i=0;i<NUMLEDS;i++)
	{
		if ( (bright!=BR_NOCHANGE) & (bright <= BR_MAX) )
		{
			leds[i].brightness = bright;
		}
	}
}



void refresh_led()
{
	int8_t i,j;


	static uint8_t led_loc[3*NUMLEDS]; // 3 -> 72 Bytes
	uint16_t color;
  j=0;
	for (i=NUMLEDS-1;i>=0;i--)
	{
		color = (leds[i].gruen * leds[i].brightness)/BR_MAX;
		led_loc[3*j] =	(uint8_t) color;
		color = (leds[i].rot * leds[i].brightness)/BR_MAX;
		led_loc[3*j+1] = (uint8_t) color;
		color = (leds[i].blau * leds[i].brightness)/BR_MAX;
		led_loc[3*j+2] = (uint8_t) color;
		j++;
	}
  while (WS_out(led_loc,NUMLEDS*3,GammaTable)!=0)
	{
		//LEDROT_TOGGLE;
		_delay_us(300);
	}
}


void outputLEDs()
{
  while (WS_out((uint8_t *)leds,NUMLEDS*3,GammaTable)!=0)
  {
  }
}

