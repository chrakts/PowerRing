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

static const uint8_t PROGMEM GammaTable[] = GCN_TABLE7TO8;

FARBE leds[NUMLEDS] = {};

uint16_t AutoGain[20]= {0,0,0,10,15,20,40,80,160,320,640,1280,2560,5120,10240,20480,2560,30960,35960,40960};

//                 Rot  GRÜN BLAU
FARBE iFarbe[16]={{0x00,0x00,0x00},// F_BLACK
                  {0x00,0x00,0x7f},// F_BLAU
                  {0x7f,0x7f,0x7f},// F_WEISS
                  {0x7f,0x00,0x00},// F_ROT
                  {0x00,0x7f,0x00},// F_GRUEN
                  {0x7f,0x00,0x7f},// F_LILA
                  {0x7f,0x5f,0x25},// F_ORANGE
                  {0x7f,0x35,0x35},// F_MAGENTA
                  {0x00,0x7f,0x7f},// F_TUERKIS
                  {0x7f,0x7f,0x00}, // F_MINT
                  {0x7f,0x70,0x3f}, // F_GELB
                 };

void set_led_autobright(uint16_t lumi)
{
int i=19;
	while( (lumi<AutoGain[i]) & (i!=0) )
		i--;
	fill_led_brightness(i+1);
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
	static uint8_t led_loc[3*NUMLEDS]; // 3
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
		//TEST_TOGGLE;
		_delay_us(300);
	}
}

void outputLEDs()
{
  while (WS_out((uint8_t *)leds,NUMLEDS*3,GammaTable)!=0)
  {
  }
}
