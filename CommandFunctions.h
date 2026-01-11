/*
 * CommandFunctions.h
 *
 * Created: 26.04.2017 14:55:18
 *  Author: a16007
 */


#ifndef COMMANDFUNCTIONS_H_
#define COMMANDFUNCTIONS_H_

#include "PowerRing.h"
extern COMMAND cnetCommands[];
extern INFORMATION information[];

#define NUM_COMMANDS 0+CMULTI_STANDARD_NUM
#define NUM_INFORMATION 5


void gotNewPower();

#endif /* COMMANDFUNCTIONS_H_ */
