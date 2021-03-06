/*
 * LED.h
 *
 * Created: 13.02.2016 12:25:18
 *  Author: Christof
 */

#ifndef LED_H_
#define LED_H_

#define NUMLEDS 24


struct str_farbe
{
	uint8_t rot;
	uint8_t gruen;
	uint8_t blau;
	uint8_t brightness;
};

typedef struct str_farbe FARBE;

enum{C_SCHWARZ=65,C_BLAU,C_WEISS,C_ROT,C_GRUEN,C_LILA,C_ORANGE,C_MAGENTA,C_TUERKIS,C_MINT,C_GELB};

extern FARBE leds[NUMLEDS];
extern FARBE iFarbe[16];

#define BR_NOCHANGE 255
#define BR_MAX		20
#define BR_HALF		10
//                Rot  GRÜN BLAU
#define F_BLACK		0x00,0x00,0x00
#define F_BLAU		0x00,0x00,0x7f
#define F_WEISS		0x7f,0x7f,0x7f
#define F_ROT		  0x7f,0x00,0x00
#define F_GRUEN		0x00,0x7f,0x00
#define F_LILA		0x5f,0x00,0x7f
#define F_ORANGE	0x7f,0x5f,0x25
#define F_MAGENTA 0x7f,0x35,0x35
#define F_TUERKIS 0x00,0x7f,0x7f
#define F_MINT    0x7f,0x7f,0x00
#define F_GELB		0x7f,0x70,0x3f

void bar_led_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright,uint8_t start, uint8_t ende);
void set_led_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright,uint8_t index);
void fill_led_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright);
void fill_led_brightness(uint8_t bright);
void fill_bar_color(uint8_t r,uint8_t g,uint8_t b,uint8_t bright);
void refresh_led();
void refresh_led_new();
void set_led_autobright(uint16_t lumi);
void outputLEDs();

#endif /* LED_H_ */
