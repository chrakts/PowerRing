/*
 * CommandFunctions.cpp
 *
 * Created: 26.04.2017 14:54:45
 *  Author: a16007
 */

#include "CommandFunctions.h"
#include "External.h"
#include "../Secrets/secrets.h"
#include "powerCalc.h"

INFORMATION information[NUM_INFORMATION]=
{
  {"HA",'E','B','a',FLOAT,1,&powerBatterie,gotNewPower},
  {"HA",'E','S','a',FLOAT,1,&powerSolar,gotNewPower},
  {"HA",'E','G','a',FLOAT,1,&powerGrid,gotNewPower}
};

COMMAND cnetCommands[NUM_COMMANDS] =
{
  cmultiStandardCommands,
};

void gotNewPower()
{
  updateLED = true;
}
