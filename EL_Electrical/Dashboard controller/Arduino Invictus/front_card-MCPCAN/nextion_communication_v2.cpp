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
                    
****************************************************************/
#include "nextion_communication_v2.h"
#include <String.h>
/**************************************************************************/
//    Variables
/**************************************************************************/

String pageName[4]={"start","display_pro","display_diag","display_fun"};
bool oilWarning=false;
bool nvOilBlinking=false;
bool precOilBlinking=false;
int minOilPress=130;
int min1OilPress=130;
int min2OilPress=100;
int min1WaterTemp=108;
int min2WaterTemp=100;
int min1Voltage=11.2;
int min2Voltage=10.5;
float oil_new=0;
float oil_old=0;
float tps_old=0;
float tps_new=0;
float map_old=0;
float map_new=0;
float lambda_old=0;
int lambda_new=0;
float doil=0;
float dtps=0;
float dmap=0;
float dlambda=0;

float seuildoil=100;
float seuildlambda=100;
float seuildmap=100;
float seuildtps=100;
unsigned long t=0;
unsigned long tdt=0;
extern float dt;

/**************************************************************************/
//    Functions
/**************************************************************************/

void changePage(int page){
  Serial1.print("page ");
  Serial1.print(page);
  nextion_endMessage();
}


void updateDisplay(int page,char gear,float oilPress, float voltage,int rpm, bool launch){
  if(page==1){
    setGear(gear);
    setOil(oilPress, rpm);
    setVoltage(voltage);
    setLaunch(page,launch);
  }
  if(page==2){
    setGear(gear);
    setOil(oilPress, rpm);
    setVoltage(voltage);
    setRPM(rpm);
    setLaunch(page,launch);
  }
}

void setOil(float oilPressure, int RPM){
  //Oil value is sent to Nextion
  Serial1.print("oil_v.val=");
  Serial1.print(oilPressure);
  nextion_endMessage();
  oil_old=oil_new;
  oil_new=oilPressure;
  doil=abs(oil_new-oil_old)/dt;
  if(doil>seuildoil){
	  Serial1.print("problem.txt=oil");
  }
  if(RPM<500){
	  minOilPress=min2OilPress;
  }
  else{
	  minOilPress=min1OilPress;
  }
  if((oilPressure<minOilPress) && !(oilWarning)){
    //Oil problem begins : variables should be initiated
    oilWarning=true;
    t=millis();
    tdt=millis();
    nvOilBlinking=true;
  }
  if((oilPressure<minOilPress) && oilWarning){
    //Oil problem continues : should the oil logo be displayed?
    tdt=millis();
    if((tdt-t)%400<200){
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
      Serial1.print("oil.pic=");
      Serial1.print(7);
      nextion_endMessage();
    }
    else{
      //There is no oil logo displayed
      Serial1.print("oil.pic=");
      Serial1.print(5);
      nextion_endMessage();
    }
  }
}

void setGear(char gear){
  Serial1.print("gear.txt=");
  Serial1.print("\"");
  Serial1.print(gear);
  Serial1.print("\"");
  nextion_endMessage();
}

void setFuel(float fuel){
	Serial1.print("fuel.val=");
	Serial1.print(fuel);
	nextion_endMessage();
}

void setWaterTemp(float waterTemp){
  //Water temp value is sent to Nextion
  Serial1.print("water_temp.val=");
  Serial1.print(waterTemp);
  nextion_endMessage();
  if(waterTemp>min1WaterTemp){ //min2WaterTemp=100 and min1WaterTemp=108
    //Water temp is below critical value
    Serial1.print("water.pic=");
    Serial1.print(7);
    nextion_endMessage();
  }
  else{
    //Water temp is not below critical value
    if(waterTemp>min2WaterTemp){ 
      //Water temp can still be dangerous
      Serial1.print("water.pic=");
      Serial1.print(8);
      nextion_endMessage();
    }
    else{
      //Water temp is normal
      Serial1.print("water.pic=");
      Serial1.print(5);
      nextion_endMessage();
    }
  }
}

void setVoltage(float voltage){
  Serial1.print("voltage.val=");
  Serial1.print(voltage);
  nextion_endMessage();
  if(voltage<min2Voltage){ //10.5V
    //Voltage is below critical value
    Serial1.print("volt.pic=");
    Serial1.print(11);
    nextion_endMessage();
  }
  else{
    //Voltage is not below critical value
    if(voltage<min1Voltage){ //min=11.2V
      //Voltage can still be dangerous
      Serial1.print("volt.pic=");
      Serial1.print(12);
      nextion_endMessage();
    }
    else{
      //Voltage is normal
      Serial1.print("volt.pic=");
      Serial1.print(5);
      nextion_endMessage();
    }
  }
}

void setRPM(int RPM){
  Serial1.print("rpm.val=");
  Serial1.print(RPM);
  nextion_endMessage();
}

void setThrottle(float throttle){
  tps_old=tps_new;
  tps_new=throttle;
  dtps=abs(tps_new-tps_old)/dt;
  if(dtps>seuildtps){
	  Serial1.print("problem.txt=oil");
  }
  Serial1.print("throttle.val=");
  Serial1.print(throttle);
  nextion_endMessage();
}

void setPlenum(float plenum){
  map_old=map_new;
  map_new=plenum;
  dmap=abs(map_new-map_old)/dt;
  if(dmap>seuildmap){
	  Serial1.print("problem.txt=MAP");
  }
  Serial1.print("plenum.val=");
  Serial1.print(plenum);
  nextion_endMessage();
}

void setLambda(float lambda){
  Serial1.print("lambda.val=");
  Serial1.print(lambda);
  nextion_endMessage();
  lambda_old=lambda_new;
  lambda_new=lambda;
  dlambda=abs(lambda_new-lambda_old)/dt;
  if(dlambda>seuildlambda){
	  Serial1.print("problem.txt=lambda");
  }
}

void setRaceCapture(bool raceOn){
  if (raceOn){
    Serial1.print("racecapt.pic=");
    Serial1.print(5);
    nextion_endMessage();
  }
  else{
    Serial1.print("racecapt.pic=");
    Serial1.print(4);
    nextion_endMessage();
  }
}

void setLaunch(int page,bool launchControl_active){
  if(launchControl_active){
    //The screen turns green if launch control is active
    Serial1.print(pageName[page]);
    Serial1.print(".bco=");
    Serial1.print(1441);
    nextion_endMessage();
  }
  else{
    //The screen turns black if launch control is inactive
    Serial1.print(pageName[page]);
    Serial1.print(".bco=");
    Serial1.print(0);
    nextion_endMessage();
  }
}

void nextion_endMessage(){
  //This message must be sent to confirm the end of the message
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
}

/***************************************************************************
  END FILE
***************************************************************************/
