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
  {"HA",'E','G','a',FLOAT,1,&powerGrid,gotNewPower},
  {"HA",'B','L','a',FLOAT,1,&batterieStatus,gotNewPower},
  {"CQ",'C','1','l',FLOAT,1,&helligkeitAussen,NULL},
  {"Me",'S','D','0',NOPARAMETER,0,NULL,clearDebugging},
  {"Me",'S','D','1',NOPARAMETER,0,NULL,setDebugging},
  {"Me",'S','N','0',NOPARAMETER,0,NULL,deactivateNachtabschaltung},
  {"Me",'S','N','1',NOPARAMETER,0,NULL,activateNachtabschaltung}
};

COMMAND cnetCommands[NUM_COMMANDS] =
{
  cmultiStandardCommands,
};

void setDebugging()
{
  doDebugging = true;
}

void clearDebugging()
{
  doDebugging = false;
}

void activateNachtabschaltung()
{
  Nachtabschaltung = true;
}

void deactivateNachtabschaltung()
{
  Nachtabschaltung = false;
}

void gotNewPower()
{
  updateLED = true;
  if( doDebugging )
    LEDROT_TOGGLE;
  else
    LEDROT_OFF;
}

