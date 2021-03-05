#ifndef nextion_communication_v2
#define nextion_communication_v2

/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/
#include <Arduino.h>

/**************************************************************************/
//    Variables
/**************************************************************************/

/**************************************************************************/
//    Functions
/**************************************************************************/
void changePage(int page);

void updateDisplay(int page,char gear,float oilPress, float voltage,int rpm,bool launch);

void setOil(float oilPress, int RPM);

void setGear(char gear);

void setFuel(float fuel);

void setWaterTemp(int waterTemp);

void setVoltage(float voltage);

void setRPM(int RPM);

void setThrottle(float throttle);

void setPlenum(float plenum);

void setLambda(float lambda);

void setRaceCapture(bool raceOn);

void setLaunch(int page,bool launchControl_active);

void nextion_endMessage();




#endif
