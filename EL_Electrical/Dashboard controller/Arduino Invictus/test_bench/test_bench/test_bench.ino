#include "nextion_communication.h"
#include "shiftlight.h"
#include "projectconfig.h"
#include <stdio.h>
int RPM;
int gear;
int nvpage;
int ancpage;
int choixPage;
char vitesse[6]={'N','1','2','3','4','5'};
int oilTemp;
int voltage;
int launch;

void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);
  pinMode(RED_SHIFT_PIN,OUTPUT);
  pinMode(BLUE_SHIFT_PIN,OUTPUT);
  startDisplay(BLUE_SHIFT_PIN,RED_SHIFT_PIN);
  RPM=0;
  gear=0;
  ancpage=1;
  nvpage=1;
  choixPage=0;
  oilTemp=0;
  voltage=0;
  launch=false;
}

void loop() {
  if(analogRead(LAUNCH_PIN)>500)
  {
    fakeLaunch();
  }
//  RPM=analogRead(POT_PIN);
//  if(RPM>800)
//  {
//    digitalWrite(RED_SHIFT_PIN,HIGH);
//  }
//  else{
//    digitalWrite(RED_SHIFT_PIN,LOW);
//  }
//  if(RPM>500)
//  {
//    digitalWrite(BLUE_SHIFT_PIN,HIGH);
//  }
//  else{
//    digitalWrite(BLUE_SHIFT_PIN,LOW);
//  }
  choixPage=analogRead(POT_PIN);
  Serial.println(choixPage);
  if(choixPage<700 && choixPage>500){
    nvpage=3;
  }
  else if(choixPage<500 && choixPage>300){
    nvpage=2;
  }
  else if(choixPage<300){
    nvpage=1;
  }
  if(analogRead(GEAR_UP_PIN)>500)
  {
    if(gear<=4){
      gear+=1;
      setGear(vitesse[gear]);
    }
  }
  if(analogRead(GEAR_DOWN_PIN)>500)
  {
    if(gear>=1){
      gear-=1;
      setGear(vitesse[gear]);
    }
  }
  if(nvpage!=ancpage){//Changement de page
    changePage(nvpage);
    ancpage=nvpage;
    updateDisplay(nvpage,gear,oilTemp,voltage,RPM,launch);
  }
}

void fakeLaunch(){
  setLaunch(true);
  delay(5000);
  setLaunch(false);
}
