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
              setOil(int oilPress)
                    Updates oil pressure in kPa and displays:
                        - Oil pressure in kPa for motor_bench page
                        - A red oil logo if oil pressure is below 1.3 bar while motor is working, or 1.0 bar if it isn't
			  setFuel(int fuel)
					Updates fuel pressure display
              setWaterTemp(int waterTemp)
                    Updates water temperature in Celsius degrees and displays:
                        - The water temperature in °C for every page
                        - An orange water temperature logo if water temperature is between 100°C and 108°C
                        - A red water temperature logo if water temperature is above 108°C
              setVoltage(int voltage)
                    Updates battery voltage(in diciVolts)and displays :
                        - The battery voltage in V for every page
                        - An orange battery logo if voltage is below 11.2V
                        - A red battery logo if voltage is below 10.5V
              setRPM(int RPM)
                    Updates the RPM display and does the following :
                        - Puts on the blue shiftlight if RPM is above critical value
                        - Puts on the red shiftlight if RPM is above danger value
              setThrottle(int throttle)
                    Updates the throttle display (in degrees)
              setPlenum(int plenum)
                    Updates the plenum pressure display (in kPa)
              setLambda(int lambda)
                    Updates the lambda value display (in percentage)
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
int min1OilPress=130;
int min2oilPress=100;
int min1WaterTemp=108;
int min2WaterTemp=100;
int min1Voltage=11.2;
int min2Voltage=10.5;
int min1Rpm=500;
int min2Rpm=500;
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
  //Oil value is sent to Nextion
  Serial2.print("oil_v.val=");
  Serial2.print(oilPressure);
  nextion_endMessage();
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

void setFuel(int fuel){
	Serial2.print("fuel.val=");
	Serial2.print(fuel);
	nextion_endMessage();
}

void setWaterTemp(int waterTemp){
  //Water temp value is sent to Nextion
  Serial2.print("water_temp.val=");
  Serial2.print(waterTemp);
  nextion_endMessage();
  if(waterTemp<min2WaterTemp){
    //Water temp is below critical value
    Serial2.print("water.pic=");
    Serial2.print(7);
    nextion_endMessage();
  }
  else{
    //Water temp is not below critical value
    if(waterTemp<min1WaterTemp){
      //Water temp can still be dangerous
      Serial2.print("water.pic=");
      Serial2.print(8);
      nextion_endMessage();
    }
    else{
      //Water temp is normal
      Serial2.print("water.pic=");
      Serial2.print(5);
      nextion_endMessage();
    }
  }
}

void setOilPress(int oilPress){
  //Oil press value is sent to Nextion
  Serial2.print("oil_v.val=");
  Serial2.print(oilPress);
  nextion_endMessage();
  if(oilPress<min2OilPress){
    //Oil press is below critical value
    Serial2.print("oil.pic=");
    Serial2.print(9);
    nextion_endMessage();
  }
  else{
    //Oil press is not below critical value
    if(oilPress<min1OilPress){
      //Oil press can still be dangerous
      Serial2.print("oil.pic=");
      Serial2.print(10);
      nextion_endMessage();
    }
    else{
      //Oil press is normal
      Serial2.print("oil.pic=");
      Serial2.print(5);
      nextion_endMessage();
    }
  }
}

void setVoltage(int voltage){
  Serial2.print("voltage.val=");
  Serial2.print(voltage);
  nextion_endMessage();
  if(voltage<min2Voltage){
    //Voltage is below critical value
    Serial2.print("volt.pic=");
    Serial2.print(11);
    nextion_endMessage();
  }
  else{
    //Voltage is not below critical value
    if(voltage<min1Voltage){
      //Voltage can still be dangerous
      Serial2.print("volt.pic=");
      Serial2.print(12);
      nextion_endMessage();
    }
    else{
      //Voltage is normal
      Serial2.print("volt.pic=");
      Serial2.print(5);
      nextion_endMessage();
    }
  }
}

void setRPM(int RPM){
  Serial2.print("rpm.val=");
  Serial2.print(RPM);
  nextion_endMessage();
  if(RPM<min2Rpm){
    //RPM is below critical value
    setShiftlight(BLUE_SHIFT_PIN,true);
  }
  else{
    setShiftlight(BLUE_SHIFT_PIN,false);
  }
  if(RPM<min1Rpm){
    //RPM can be dangerous
    SetShiftlight(RED_SHIFT_PIN,true);
  }
  else{
    //Water temp is normal
    SetShiftlight(RED_SHIFT_PIN,false);
  }
}

void setThrottle(int throttle){
  Serial2.print("throttle.val=");
  Serial2.print(throttle);
  nextion_endMessage();
}

void setPlenum(int plenum){
  Serial2.print("plenum.val=");
  Serial2.print(plenum);
  nextion_endMessage();
}

void setLambda(int lambda){
  Serial2.print("lambda.val=");
  Serial2.print(lambda);
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
  //This message must be sent to confirm the end of the message
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

/***************************************************************************
  END FILE
***************************************************************************/
