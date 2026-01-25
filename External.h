/*
 * External.h
 *
 * Created: 03.04.2017 21:04:41
 *  Author: Christof
 */



#ifndef EXTERNAL_H_
#define EXTERNAL_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "Communication.h"
#include "myTimers.h"
#include "ws2812Hardware.h"

extern char const *Node;
extern char IDNumber[12] EEMEM ;
extern char SerialNumber[12] EEMEM;
extern char IndexNumber[2] EEMEM;

extern bool doDebugging;

extern bool Nachtabschaltung;

extern char sLEDStatus[24];

extern volatile uint8_t updateLED;

extern char SecurityLevel;

class Communication;   // Forward declaration
class ComReceiver;
extern Communication cnet;
extern ComReceiver cnetRec;


#endif /* EXTERNAL_H_ */
