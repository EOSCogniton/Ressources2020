#ifndef nextion_communication
#define nextion_communication



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/
#include "shiftlight.h"
#include <Arduino.h>

/**************************************************************************/
//    Functions
/**************************************************************************/
void changePage(int page);

void startDisplay(int blueShiftPin,int redShiftPin);

void updateDisplay(int page,char gear,int oilTemp, float voltage,int rpm, bool launch);

void setGear(char gear);

void setOilTemp(int oilTemp);

void setVoltage(int voltage);

void setRPM(int RPM);

void setLaunch(bool launch_active);

void nextion_endMessage();

void setRaceCapture(bool raceOn);

#endif
