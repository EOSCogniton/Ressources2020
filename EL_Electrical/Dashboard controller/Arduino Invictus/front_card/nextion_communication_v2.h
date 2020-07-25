#ifndef nextion_communication_v2
#define nextion_communication_v2

/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/
#include "shiftlight.h"
#include <Arduino.h>

/**************************************************************************/
//    Variables
/**************************************************************************/

/**************************************************************************/
//    Functions
/**************************************************************************/
void changePage(int page);

void startDisplay(int blueShiftPin,int redShiftPin);

void updateDisplay(int page,char gear,int oilTemp, float voltage,int rpm, bool launch);

void setGear(char gear);

void setFuel(int fuel);

void setWaterTemp(int waterTemp);

void setVoltage(int voltage);

void setRPM(int RPM);

void setOil(int oilPress);

void setPlenum(int plenum);

void setLambda(int lambda);

void setLaunch(bool launch_active);

void nextion_endMessage();

void setRaceCapture(bool raceOn);

#endif
