/***************************************************************
  @file: front_card
  @author: Raphaël Viudès(RVS)
     for Ecurie Piston Sport Auto
      at Ecole Centrale de Lyon
  @description: countains the main program which picks up CAN data and updates the screen display
  @functions: setup()
                      Initiates ports and displays
              loop()
                      Does all the screen display process
                    
****************************************************************/
#include "nextion_communication_v2.h"
#include "shiftlight.h"
#include "projectconfig.h"
#include <stdio.h>
int RPM;
int ancgear;
int nvgear;
int nvpage;
int ancpage;
int choixPage;
char vitesse[7]={'N','1','2','3','4','5','6'};
int waterTemp;
int voltage;
bool anclaunch;
bool nvlaunch;
bool ancrace;
bool nvrace;
int oilPressure;
int throttle;
int plenum;
int lambda;

void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);
  pinMode(RED_SHIFT_PIN,OUTPUT);
  pinMode(BLUE_SHIFT_PIN,OUTPUT);
  startDisplay(BLUE_SHIFT_PIN,RED_SHIFT_PIN);
  RPM=0;
  //nvvalue is for the new value of value
  //which is compared to its prec value, ancvalue
  //in order to save screen loading times
  ancgear=0;
  nvgear=0;
  ancpage=1;
  nvpage=1;
  choixPage=0;
  waterTemp=0;
  voltage=0;
  anclaunch=false;
  nvlaunch=false;
  ancrace=false;
  nvrace=false;
  //Values should be initiated through a CAN inquiry
  oilPressure=0;
  throttle=0;
  plenum=0;
  lambda=0;
}

void loop() {
  //This part is for a pot which swaps between pages
  choixPage=analogRead(POT_PIN);
  if(choixPage<700){
    nvpage=3;
  }
  if(choixPage<500){
    nvpage=2;
  }
  if(choixPage<300){
    nvpage=1;
  }
  if(nvpage!=ancpage){//Changing page
    changePage(nvpage);
    ancpage=nvpage;
    updateDisplay(nvpage,nvgear,oilTemp,voltage,RPM,nvlaunch);
  }
  if(nvgear!=ancgear){//Changing gear
    ancgear=nvgear;
    setGear(vitesse[nvgear]);
  }
  if(nvrace!=ancrace){//Changing race capture activation state
    ancrace=nvrace;
    setRaceCapture(nvrace);
  }
  if(nvlaunch!=anclaunch){
    anclaunch=nvlaunch;
    setLaunch(launch);
  }
  setWaterTemp(waterTemp);
  setVoltage(voltage);
  setRPM(RPM);
  setOil(oilPressure);
  setThrottle(throttle);
  setPlenum(plenum);
  setLambda(lambda);
}
