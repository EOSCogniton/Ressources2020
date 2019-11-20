#include "nextion_communication.h"
#include "shiftlight.h"
#include "projectconfig.h"
#include <stdio.h>
int RPM;
int gear;
int nvpage;
int ancpage;
int choixPage;
char vitesse[7]={'N','1','2','3','4','5'};
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
  if(nvpage!=ancpage){//Changement de page
    changePage(nvpage);
    ancpage=nvpage;
    updateDisplay(nvpage,gear,oilTemp,voltage,RPM,launch);
  }
}
