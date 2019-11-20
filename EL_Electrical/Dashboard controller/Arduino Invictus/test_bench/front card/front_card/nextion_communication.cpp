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
              setOilTemp(int oilTemp)
                    Updates the display of oil temperature in Celsius degrees
              setVoltage(int voltage)
                    Updates the battery voltage(in diciVolts)
              setRPM(int RPM)
                    Updates the RPM display
              setLaunch(bool launch_active)
                    Changes display depending on launch control activation: screen
                    turns green if launch control is active, else it turns normal
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

void setGear(char gear){
  Serial2.print("gear.txt=");
  Serial2.print("\"");
  Serial2.print(gear);
  Serial2.print("\"");
  nextion_endMessage();
}

void setOilTemp(int oilTemp){
  Serial2.print("oil_temp.val=");
  Serial2.print(oilTemp);
  nextion_endMessage();
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

void setResCapture(bool resOn){
  if resOn{
    Serial2.print("racecapt.bco=");
    Serial2.print(1441);
    nextion_endMessage();
  }
  else{
    Serial2.print("racecapt.bco=");
    Serial2.print(63521);
    nextion_endMessage();
  }
}
void setLaunch(int page,bool launch_active){
  if(launch_active){
    Serial2.print("launch_state.val=");
    Serial2.print(1);
    nextion_endMessage();
    //The screen turns green if launch control is active
    Serial2.print(pageName[page]);
    Serial2.print(".bco=");
    Serial2.print(23583);
    nextion_endMessage();
    //Font backgrounds turn green too
    Serial2.print("oil_temp.bco=");
    Serial2.print(23583);
    nextion_endMessage();
    Serial2.print("voltage.bco=");
    Serial2.print(23583);
    nextion_endMessage();
    Serial2.print("gear.bco=");
    Serial2.print(23583);
    nextion_endMessage();
    //Font colors turn black
    Serial2.print("oil_temp.pco=");
    Serial2.print(0);
    nextion_endMessage();
    Serial2.print("voltage.pco=");
    Serial2.print(0);
    nextion_endMessage();
    Serial2.print("gear.pco=");
    Serial2.print(0);
    nextion_endMessage();
  }
  else{
    Serial2.print("launch_state.val=");
    Serial2.print(0);
    nextion_endMessage();
    //The screen turns black if launch control is inactive
    Serial2.print(pageName[page]);
    Serial2.print(".bco=");
    Serial2.print(4258);
    nextion_endMessage();
    //Font backgrounds turn black
    Serial2.print("oil_temp.bco=");
    Serial2.print(4258);
    nextion_endMessage();
    Serial2.print("voltage.bco=");
    Serial2.print(4258);
    nextion_endMessage();
    Serial2.print("gear.bco=");
    Serial2.print(4258);
    nextion_endMessage();
    //Font colors turn white
    Serial2.print("oil_temp.pco=");
    Serial2.print(65535);
    nextion_endMessage();
    Serial2.print("voltage.pco=");
    Serial2.print(65535);
    nextion_endMessage();
    Serial2.print("gear.pco=");
    Serial2.print(65535);
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
