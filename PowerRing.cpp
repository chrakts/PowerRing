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

	PORTC_DIRSET = PIN2_bm | PIN4_bm;
  PORTC_OUTSET = PIN2_bm;

	PORTD_DIRSET = PIN2_bm;
	PORTD_OUTSET = PIN2_bm;
  PORTD.PIN2CTRL = PORT_OPC_WIREDAND_gc;

	PORTE_DIRSET = 0b00001011;
	PORTE_DIRCLR = 0b11110100;

	uint8_t i;
	for(i=0;i<4;i++)
	{
		LEDROT_TOGGLE;
		_delay_ms(50);
	}
  LEDROT_OFF;


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
    /*bar_ring2_color(127,127,127,0,0,10);
    refresh_led();
    while(1);*/

    if(updateLED)
    {
      updateLED = false;
      calcLedsFromPower();
      calcBatterieStatus();
      refresh_led();
    }
		cnetRec.comStateMachine();
		cnetRec.doJob();
	}
}


