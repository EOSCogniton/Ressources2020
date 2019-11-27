/***************************************************************
  @file: nextion_communication
  @author: Raphaël Viudès(RVS)
     for Ecurie Piston Sport Auto
      at Ecole Centrale de Lyon
  @description: countains all the functions that permit an update of
  the values displayed on the screen
  @functions: setGear(char gear)
                    Updates the gear display on the screen according to
                    char gear(e.g. N,1,2,3,..)
              setWaterTemp(int waterTemp)
                    Updates the display of water temperature in Celsius degrees
              setVoltage(int voltage)
                    Updates the battery voltage(in diciVolts)
              setRPM(int RPM)
                    Updates the RPM display
              setLaunch(bool launch_active)
                    Changes display depending on launch control activation: screen
                    turns green if launch control is active, else it turns normal
              setRaceCapture(bool raceOn)
                    Indicator zone turns green if race capture is on, else it turns red
              nextion_endMessage()
                    Sends a message which has to be sent at the end of each communication
                    with Nextion (it's a protocol)
              changePage(int page)
                    Changes the display page
              updateDisplay(..)
                    Supposed to be called while changing page or restarting the screen
              startDisplay()
                    Called in Teensy setup to test if all display features are working properly
                    
****************************************************************/

#include "nextion_communication.h"
#include "shiftlight.h"
#include <Arduino.h>

/**************************************************************************/
//    Variables
/**************************************************************************/

char pageName[4]={'start','display_pro','display_diag','display_fun'};
bool oilWarning=false;
bool nvOilBlinking=false;
bool precOilBlinking=false;
int minOilPress=0;
unsigned long t=0;
unsigned long tdt=0;

/**************************************************************************/
//    Functions
/**************************************************************************/

void changePage(int page){
  Serial2.print("page ");
  Serial2.print(page);
  nextion_endMessage();
}

void startDisplay(int blueShiftPin,int redShiftPin){
  //Puts on the lights for 2 seconds and displays welcome page on screen
  Serial2.print("page ");
  Serial2.print(0);
  nextion_endMessage();
  setShiftLight(blueShiftPin,true);
  setShiftLight(redShiftPin,true);
  //Voir avec Bruno pour la commande d'affichage lumineux des boutons
  delay(5000);
  //Sets the screen at its work state
  Serial2.print("page ");
  Serial2.print(1);
  nextion_endMessage();
  setShiftLight(blueShiftPin,false);
  setShiftLight(redShiftPin,false);
}

void updateDisplay(int page,char gear,int oilTemp, float voltage,int rpm, bool launch){
  if(page==1){
    setGear(gear);
    setOilTemp(oilTemp);
    setVoltage(voltage);
    setLaunch(launch);
  }
  if(page==2){
    setGear(gear);
    setOilTemp(oilTemp);
    setVoltage(voltage);
    setRPM(rpm);
    setLaunch(launch);
  }
}

void setOil(int oilPressure){
  if(oilPressure<minOilPress) and not(oilWarning){
    //Oil problem begins : variables should be initiated
    oilWarning=true;
    t=millis();
    tdt=millis();
    nvOilBlinking=true;
  }
  if(oilPressure<minOilPress) and oilWarning{
    //Oil problem continues : should the oil logo be displayed?
    tdt=millis();
    if(tdt-t)%400<200{
      //In this phase, the oil logo is displayed
      nvOilBlinking=true;
    }
    else{
      //In this one... It's not
      nvOilBlinking=false;
    }
  }
  if(oilPressure>minOilPress){
    //Everything is fine! 
    tdt=0;
    t=0;
    nvOilBlinking=false;
    oilWarning=false;
  }
  if(nvOilBlinking!=precOilBlinking){
    precOilBlinking=nvOilBlinking;
    if(nvOilBlinking){
    //Oil logo is diplayed
    Serial2.print("oil.pic=");
    Serial2.print(7);
    nextion_endMessage();
  }
  else{
    //There is no oil logo displayed
    Serial2.print("oil.pic=");
    Serial2.print(5);
    nextion_endMessage();
  }
  }
}
void setGear(char gear){
  Serial2.print("gear.txt=");
  Serial2.print("\"");
  Serial2.print(gear);
  Serial2.print("\"");
  nextion_endMessage();
}

void setWaterTemp(int waterTemp){
  Serial2.print("water_temp.val=");
  Serial2.print(waterTemp);
  nextion_endMessage();
}

void setOilPress(int oilPress){
  
}

void setVoltage(int voltage){
  Serial2.print("voltage.val=");
  Serial2.print(voltage);
  nextion_endMessage();
}

void setRPM(int RPM){
  Serial2.print("rpm.val=");
  Serial2.print(RPM);
  nextion_endMessage();
}

void setRaceCapture(bool raceOn){
  if raceOn{
    Serial2.print("racecapt.pic=");
    Serial2.print(5);
    nextion_endMessage();
  }
  else{
    Serial2.print("racecapt.pic=");
    Serial2.print(4);
    nextion_endMessage();
  }
}
void setLaunch(int page,bool launch_active){
  if(launch_active){
    //The screen turns green if launch control is active
    Serial2.print(pageName[page]);
    Serial2.print(".bco=");
    Serial2.print(1441);
    nextion_endMessage();
  else{
    //The screen turns black if launch control is inactive
    Serial2.print(pageName[page]);
    Serial2.print(".bco=");
    Serial2.print(0);
    nextion_endMessage();
    }
}

void nextion_endMessage(){
  //This message must be sent as a confirmation of the end of the message
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

/***************************************************************************
  END FILE
***************************************************************************/
