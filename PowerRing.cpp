/*
* PowerRing.cpp
*
* Created: 16.03.2017 13:03:01
* Author : a16007
*/

#include "PowerRing.h"

void setup()
{
  init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION); //
	PORTA_DIRSET = PIN2_bm | PIN3_bm | PIN4_bm;
	PORTA_OUTSET = 0xff;

	PORTB_DIRSET = 0xff;

	PORTC_DIRSET = PIN1_bm;

	PORTD_DIRSET = PIN0_bm | PIN4_bm | PIN5_bm | PIN7_bm;
	PORTD_DIRCLR = PIN6_bm;
	PORTD_OUTCLR = PIN4_bm | PIN5_bm;

	PORTE_DIRSET = 0xff;

	uint8_t i;

	for(i=0;i<20;i++)
	{
		LEDGRUEN_TOGGLE;
		_delay_ms(50);
	}
  LEDGRUEN_OFF;

	PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();

	cnet.open(Serial::BAUD_57600,F_CPU);
}

int main(void)
{
	setup();
	cnet.broadcastUInt8((uint8_t) RST.STATUS,'S','0','R');
	init_mytimer();
  WS_init();

	while (1)
	{
    if(updateLED)
    {
      updateLED = false;
      calcLedsFromPower();
      refresh_led();
    }
		cnetRec.comStateMachine();
		cnetRec.doJob();
	}
}


