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
#include "projectconfig.h"
#include "can_interface.h"
#include <stdio.h>
#include <SPI.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>


int ancgear;
int nvgear;
int nvpage;
int ancpage;
boolean changementPage;
char vitesse[7]={'N','1','2','3','4','5','6'};
bool anclaunch;
bool nvlaunch;
bool ancrace;
bool nvrace;
unsigned long TchgtPage;

int rpm_old=0;
int rpm_new=0;
int drpm=0;
int seuildrpm=100;
float dt=0.05;
int min1Rpm=11500;
int min2Rpm=12000;

int homing, neutre,log_DTA, TC_control, launch_control, Wet_ON;

//Initialization of CANBUS
can_interface CAN;
IntervalTimer CANTimer;
unsigned long Can_send_period=75000; //On envoie sur le can toutes les 75ms
//header des fonctions
void Can_Send();
void setRPMShiftLight(int RPM);

void setup() {
  //définition des entrées-sorties
  pinMode(Neutre_button,INPUT_PULLUP);
  pinMode(Homing_button,INPUT_PULLUP);
  pinMode(LaunchControl_button,INPUT_PULLUP);
  pinMode(WD_Switch,INPUT_PULLUP);
  pinMode(TC_Switch,INPUT_PULLUP);
  pinMode(Log_switch,INPUT_PULLUP);
  pinMode(RED_SHIFT_PIN,OUTPUT);
  pinMode(BLUE_SHIFT_PIN,OUTPUT);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  //Initialisation of the variables used in the program
  homing=1;
  neutre=1;
  log_DTA=1;
  TC_control=1;
  launch_control=1;
  Wet_ON=1;
  
  //nvvalue is for the new value of value
  //which is compared to its prec value, ancvalue
  //in order to save screen loading times 
  ancgear=0;
  ancpage=1;
  nvpage=1;
  TchgtPage=0;
  changementPage=false;
  anclaunch=false;
  nvlaunch=false;
  ancrace=false;
  nvrace=false;
  
  Serial2.begin(9600);
  Serial.begin(9600);

  
  //Start display
  //Puts on the lights for 2 seconds and displays welcome page on screen
  Serial2.print("page ");
  Serial2.print(0);
  nextion_endMessage();
  digitalWrite(BLUE_SHIFT_PIN,HIGH);
  digitalWrite(RED_SHIFT_PIN,HIGH);
  //Voir avec Bruno pour la commande d'affichage lumineux des boutons
  delay(2000);
  //Sets the screen at its work state
  Serial2.print("page ");
  Serial2.print(1);
  nextion_endMessage();
  digitalWrite(BLUE_SHIFT_PIN,LOW);
  digitalWrite(RED_SHIFT_PIN,LOW);
  
  //Can et interruption
  //Define Timer
  CANTimer.begin(Can_Send, Can_send_period); //each period of the Timer the function Can_Send is launched
}

void loop() {
  CAN.Recieve();
  homing=digitalRead(Homing_button);
  neutre=digitalRead(Neutre_button);
  log_DTA=digitalRead(Log_switch);
  TC_control=digitalRead(TC_Switch);
  launch_control=digitalRead(LaunchControl_button);
  Wet_ON=digitalRead(WD_Switch);

  if ( !homing)
  {
    Serial.println("appui homing");
  }
  if ( !neutre)
  {
    Serial.println("appui neutre");
  }
  if(!log_DTA)
  {
    Serial.println("log dta activé");
  }
  if(!TC_control)
  {
    Serial.println("TC_control activé");
  }
  if(!launch_control)
  {
    Serial.println("launch_control activé");
  }
  if(!Wet_ON)
  {
    Serial.println("Wet_ON activé");
  }
  
  //Shift light :on allume en fonction des rpms pour savoir si on change de vitesse
  setRPMShiftLight(CAN.RPM);
  
  //This part is for a button which swaps between pages
  changementPage=digitalRead(Chgt_screen_button)*true; //Quand on appuie sur l'écran ou le bouton ( à voir car il n'y a pas de connexion avec le bouton) il faut changer de page;
  TchgtPage=millis()-TchgtPage;
  if(changementPage && TchgtPage>500) //On regarde si cela fait plus de 500ms qu'on a voulu changer de page (Permet d'éviter le fait qu'on est plusieurs loop avec changementPage qui reste à 1 alors que c'est le même appui)
  {
    if(ancpage==2)
    {
      nvpage=1;
    }
    else
    {
      nvpage=ancpage+1;
    }
    changePage(nvpage);
    ancpage=nvpage;
    updateDisplay(nvpage,CAN.gear,CAN.oilPressure,CAN.Volts,CAN.RPM,nvlaunch);
  }
  if(CAN.gear!=ancgear){//Changing gear
    ancgear=CAN.gear;
    setGear(vitesse[nvgear]);
  }
  if(nvrace!=ancrace){//Changing race capture activation state
    ancrace=nvrace;
    setRaceCapture(nvrace);
  }
  if(nvlaunch!=anclaunch){
    anclaunch=nvlaunch;
    setLaunch(ancpage,nvlaunch);
  }
  setWaterTemp(CAN.waterTemp);
  setVoltage(CAN.Volts);
  setRPM(CAN.RPM);
  setOil(CAN.oilPressure,CAN.RPM);
  setThrottle(CAN.throttle);
  setPlenum(CAN.plenum);
  setLambda(CAN.Lambda);
}

void setRPMShiftLight(int RPM)
{
  rpm_old=rpm_new;
  rpm_new=RPM;
  drpm=abs(rpm_new-rpm_old)/dt;
  if(drpm>seuildrpm){
    Serial2.print("problem.txt=rpm");
  }
  if(RPM<min1Rpm) //min1Rpm=11500; min2Rpm=12000
  {
    digitalWrite(BLUE_SHIFT_PIN,LOW);
    digitalWrite(RED_SHIFT_PIN,LOW);
  } else if( RPM<min2Rpm)
  {
    digitalWrite(BLUE_SHIFT_PIN,HIGH);
    digitalWrite(RED_SHIFT_PIN,LOW);
  } else{
    digitalWrite(BLUE_SHIFT_PIN,HIGH);
    digitalWrite(RED_SHIFT_PIN,HIGH);
  }
}

void Can_Send()
{
  CAN.Transmit(homing, neutre,log_DTA, TC_control, launch_control, Wet_ON);
}
