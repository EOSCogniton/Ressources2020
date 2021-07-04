

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


int flag;
int ancgear;
int nvpage;
int ancpage;
bool changementPage;
bool changementPageprec;
char vitesse[9]={'N','1','2','3','4','5','6','E','H'};
bool anclaunch;
bool nvlaunch;
bool ancrace;
bool nvrace;
bool ancauto_mode;
unsigned long TchgtPage;
unsigned long T1;

int rpm_old=0;
int rpm_new=0;
int drpm=0;
int seuildrpm=500;
float dt=0.05;
const int RPM_shift_up[5] = {13000,11900,11500,11200,11000};
int min1Rpm=11500;
int min2Rpm=12000;
int meme_display=0;
int homing, neutre,log_DTA, TC_control, launch_control, Wet_ON;

//Initialization of CANBUS
can_interface CAN;
IntervalTimer CANTimer;
unsigned long Can_send_period=150; //On envoie sur le can toutes les 150ms
unsigned long Last_can_send; //On retient quand on a envoyé le can la dernière fois

void setup() {
  //Init CAN
      // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled
    if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK){
        Serial.println("Init Successfully!");
        digitalWrite(13,HIGH);
    }
    else{
        Serial.println("Init Failure");
    }

    // Set operation mode to normal so the MCP2515 sends acks to received data
    CAN0.setMode(MCP_NORMAL);                  

    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT);  

    
  //définition des entrées-sorties
  pinMode(Neutre_button,INPUT_PULLUP);
  pinMode(Homing_button,INPUT_PULLUP);
  pinMode(LaunchControl_button,INPUT_PULLUP);
  pinMode(WD_Switch,INPUT_PULLUP);
  pinMode(TC_Switch,INPUT_PULLUP);
  pinMode(Log_switch,INPUT_PULLUP);
  pinMode(Chgt_screen_button,INPUT_PULLUP);
  pinMode(RED_SHIFT_PIN,OUTPUT);
  pinMode(BLUE_SHIFT_PIN,OUTPUT);
  
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
  ancauto_mode=false;
  
  Serial.begin(9600);
  Serial1.begin(9600);


  //Start display
  //Puts on the lights for 2 seconds and displays welcome page on screen
  Serial1.print("page ");
  Serial1.print(0);
  nextion_endMessage();
  digitalWrite(BLUE_SHIFT_PIN,HIGH);
  digitalWrite(RED_SHIFT_PIN,HIGH);
  //Voir avec Bruno pour la commande d'affichage lumineux des boutons
  delay(1000);
  //Sets the screen at its work state
  Serial1.print("page ");
  Serial1.print(2);
  nextion_endMessage();
  digitalWrite(BLUE_SHIFT_PIN,LOW);
  digitalWrite(RED_SHIFT_PIN,LOW);
  
  //Can et interruption
  //Define Timer
  //CANTimer.begin(Can_Send, Can_send_period); //each period of the Timer the function Can_Send is launched
}

void loop() {
  if (millis()-Last_can_send>Can_send_period)  
  {
    Can_Send();
    Last_can_send = millis();
    }
  CAN.Recieve(); // on lit tout le temps le can et une fois sur 5 on mets à jour l'écran
  
  delay(7);

  
  homing=digitalRead(Homing_button);
  neutre=digitalRead(Neutre_button);
  log_DTA=digitalRead(Log_switch);
  TC_control=digitalRead(TC_Switch);
  launch_control=digitalRead(LaunchControl_button);
  Wet_ON=digitalRead(WD_Switch);

  if (!homing)
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
    Serial.println("Dry activé");
  }
  if (CAN.auto_mode!=ancauto_mode)
  {
    if (CAN.auto_mode==true)
    {
     digitalWrite(BLUE_SHIFT_PIN,HIGH);
     digitalWrite(RED_SHIFT_PIN,HIGH); 
    }
    else
    {
      digitalWrite(BLUE_SHIFT_PIN,LOW);
      digitalWrite(RED_SHIFT_PIN,LOW);
    }
    ancauto_mode = CAN.auto_mode;
    Serial.print("auto mode : ");
    Serial.println(ancauto_mode);
  }
  
  
  
  //Shift light :si on n'est pas en passage automatique des vitesses on allume en fonction des rpms pour savoir si on change de vitesse
  if (ancauto_mode!=true)
  {
    setRPMShiftLight(CAN.RPM, CAN.gear);
  }
   flag = flag + 1;
  if (flag == 40) { 
    flag = 0; 
  //This part is for a button which swaps between pages
  changementPageprec = changementPage;
  changementPage=digitalRead(Chgt_screen_button); //Quand on appuie sur l'écran ou le bouton ( à voir car il n'y a pas de connexion avec le bouton) il faut changer de page;
  
  if( !changementPage && changementPage!=changementPageprec && (millis()-TchgtPage)>700) //On regarde si cela fait plus de 500ms qu'on a voulu changer de page (Permet d'éviter le fait qu'on est plusieurs loop avec changementPage qui reste à 1 alors que c'est le même appui)
  {
    meme_display = 0;
    TchgtPage=millis();
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
    updateDisplay(nvpage,vitesse[CAN.gear],CAN.oilPressure,CAN.Volts,CAN.RPM,CAN.LC_state);
  }
  else if ( !changementPage && changementPage!=changementPageprec) {//Petit photo de pso qui fait bien plaisir le couz
    meme_display = meme_display+1;
    if (meme_display==2)
    {
      meme_display = 0;
      changePage(3);
    }
  }
  
  if(CAN.gear!=ancgear || (CAN.errorMotored==1)) {//Changing gear
    if(CAN.errorMotored==1) {
      setGear(vitesse[7]);
    }
    else {
      ancgear=CAN.gear;
      setGear(vitesse[CAN.gear]);
    }
  }
  
  if(nvrace!=ancrace){//Changing race capture activation state
    ancrace=nvrace;
    setRaceCapture(nvrace);
  }
  if(CAN.LC_state!=anclaunch){
    anclaunch=CAN.LC_state;
    setLaunch(ancpage,CAN.LC_state);
  }
  setWaterTemp(CAN.waterTemp);
  setVoltage(CAN.Volts);
  setRPM(CAN.RPM);
  setOil(CAN.oilPressure,CAN.RPM);
  setThrottle(CAN.throttle);
  setPlenum(CAN.plenum);
  setLambda(CAN.Lambda);
  setFuel(CAN.FuelPressure);
  setRaceCapture (CAN.logRC);
  }
}

void setRPMShiftLight(int RPM, int gearValue)
{
  rpm_old=rpm_new;
  rpm_new=RPM;
  drpm=abs(rpm_new-rpm_old)/dt;
  if(drpm>seuildrpm){
    Serial1.print("problem.txt=rpm");
    nextion_endMessage();
  }
  switch (gearValue) {
    case 1:
      if(RPM<(RPM_shift_up[0]-500)) //min1Rpm=11500; min2Rpm=12000 Edit: Le seuil de RPM de passage de vitesse depend du rapport engager. 500 correspond a la variation de RPM que l'on veut entre l'allumage de la premiere et de la deuxieme led
      {
        digitalWrite(BLUE_SHIFT_PIN,LOW);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else if( RPM<RPM_shift_up[0])
      {
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else{
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,HIGH);
      }
      break;
    
    case 2:
      if(RPM<(RPM_shift_up[1]-500)) //min1Rpm=11500; min2Rpm=12000 Edit: Le seuil de RPM de passage de vitesse depend du rapport engager. 500 correspond a la variation de RPM que l'on veut entre l'allumage de la premiere et de la deuxieme led
      {
        digitalWrite(BLUE_SHIFT_PIN,LOW);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else if( RPM<RPM_shift_up[1])
      {
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else{
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,HIGH);
      }
      break;
      
     case 3:
      if(RPM<(RPM_shift_up[2]-500)) //min1Rpm=11500; min2Rpm=12000 Edit: Le seuil de RPM de passage de vitesse depend du rapport engager. 500 correspond a la variation de RPM que l'on veut entre l'allumage de la premiere et de la deuxieme led
      {
        digitalWrite(BLUE_SHIFT_PIN,LOW);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else if( RPM<RPM_shift_up[2])
      {
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else{
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,HIGH);
      }
      break; 
     
    case 4:
      if(RPM<(RPM_shift_up[3]-500)) //min1Rpm=11500; min2Rpm=12000 Edit: Le seuil de RPM de passage de vitesse depend du rapport engager. 500 correspond a la variation de RPM que l'on veut entre l'allumage de la premiere et de la deuxieme led
      {
        digitalWrite(BLUE_SHIFT_PIN,LOW);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else if( RPM<RPM_shift_up[3])
      {
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else{
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,HIGH);
      }
      break;
      
    case 5:
      if(RPM<(RPM_shift_up[4]-500)) //min1Rpm=11500; min2Rpm=12000 Edit: Le seuil de RPM de passage de vitesse depend du rapport engager. 500 correspond a la variation de RPM que l'on veut entre l'allumage de la premiere et de la deuxieme led
      {
        digitalWrite(BLUE_SHIFT_PIN,LOW);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else if( RPM<RPM_shift_up[4])
      {
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else{
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,HIGH);
      }
      break;
      
    case 8:
      if(RPM<6500) // Edit: Le seuil de RPM de passage de vitesse depend du rapport engager. 500 correspond a la variation de RPM que l'on veut entre l'allumage de la premiere et de la deuxieme led
      {
        digitalWrite(BLUE_SHIFT_PIN,LOW);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else if(RPM<7000)
      {
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,LOW);
      } else{
        digitalWrite(BLUE_SHIFT_PIN,HIGH);
        digitalWrite(RED_SHIFT_PIN,HIGH);
      }
      break;
      
    default:
      digitalWrite(BLUE_SHIFT_PIN,LOW);
      digitalWrite(RED_SHIFT_PIN,LOW);
      break;
  }
}

void Can_Send()
{
  CAN.Transmit(homing, neutre,log_DTA, TC_control, launch_control, Wet_ON);
}
