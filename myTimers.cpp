#include "myTimers.h"
#include "ledHardware.h"


// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,500,0,nextReportStatus},
};


void nextReportStatus(uint8_t test)
{
	updateLED=true;
}



