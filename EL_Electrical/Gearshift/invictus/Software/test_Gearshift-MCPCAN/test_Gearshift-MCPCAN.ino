/**************************************************************************/
/*!
    @file     main_carte.cpp
    @author   Bruno Moreira Nabinger, Corentin Lepais, Bob Aubouin, Ariel Rodriguez
                        
                            (EPSA)
                   Ecurie Piston Sport Auto
    
    Main code for control the Motor with integrated Controller and CAN 
    interface BG 45 CI

 
    @section  HISTORY
    v0.95 - 10/07/2020 Add external interruptions for gear change and internal for sending CAN
    v0.9 - ~~/11/2019 Change CAN library to work with Teensy 3.2
    v0.8 - ~~/06/2019 Adding mode Auto
    v0.7 - 17/04/2019 Changed a lot of details to make the thing work
    v0.6 - 06/04/2019 Add the sending of the speed to the DTA
    v0.5 - 13/02/2019 Modifications linked to the class CAN
    v0.4 - 06/02/2019 Add fonction to can_interface
    v0.3 - 10/11/2018 Comments of code and add of the file 
           "projectconfig.h", with the definitions of the pins numbers.
    v0.2 - 17/10/2018 Management of pallets and beginning of creations of 
                      the associated functions
    v0.1 - 10/10/2018 First release (previously code of Pedro)
*/
/**************************************************************************/
#include "projectconfig.h"

//Ajout des fonctions
#include "fonct_palette_homing.h"
#include "fonct_mot.h"
#include "can_interface_mcp.h"

//Definition of used variables 
//Motor 
int engagedPosition; // Contain what motor position is currently engaged
int wantedPosition;// Contain the motor position wanted so the speed rapport of the bike
const bool motorCommand[9][4] ={ {0,0,0,0}, //motorCommand[0] = Clear error and Stop
                                 {0,0,0,1}, //motorCommand[1] = Start Homing
                                 {0,0,1,0}, //motorCommand[2] = Position 2 = Neutral gear
                                 {0,0,1,1}, //motorCommand[3] = Position 3 = Gear 1
                                 {0,1,0,0}, //motorCommand[4] = Position 4 = Gear 2
                                 {0,1,0,1}, //motorCommand[5] = Position 5 = Gear 3
                                 {0,1,1,0}, //motorCommand[6] = Position 6 = Gear 4
                                 {0,1,1,1}, //motorCommand[7] = Position 7 = Gear 5
                                 {1,0,0,0}};//motorCommand[8] = Position 8 = Gear 6
bool outMotor1; //Info return by the motor
bool outMotor2;//Info return by the motor
const int neutreCommand = 2;
const int homingCommand = 1;

//Palettes : 
const unsigned long AntiReboundDelay=200; //Delay in order to avoid signal rebound on shifter and pass two gear on one push
const int IncreaseDelay=10; //Delay to let the time to the shiftcut to do his job for an gear UP
const int DecreaseDelay=20; //Delay to let the time to the shiftcut to do his job for an gear DOWN

//Dashboard to send :    
bool error;

//DTA com
const int valAnalog[] = {0, 36, 72, 108, 144, 180, 216,256}; //voltage to send to the dta for each gear engaged

//0.45,  0.93, 1.4

//Auto
bool Auto; // if true we are in auto mode
const int RPM_shift[3] = {12500,12200,12000};
unsigned long T_ShiftAuto; //To make sur the car doesn't shift up two time in a row
signed RPM ;

//Initialization of CANBUS
int canStable; //When the Teensy power up the can is not very stable and because it affect directly the motor we need to wait a little before using the CAN
const int Canstabledelay= 30000; //Number of loop before using the CAN
can_interface CAN;
IntervalTimer CANTimer;
unsigned long Can_send_period=75000; //On envoie sur le can toutes les 75ms

void setup() 
{   
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
    
  //Initialization of the variables
  //Motor
  engagedPosition = 0; // We don't know but this normaly not the homming position
  wantedPosition = 1; // First we want to do the homming of the motor
  error = 0; // we suppose that there is no error 
  //Auto
  Auto = false; //we start in normal mode
  T_ShiftAuto = 0;
  //CAN
  canStable = 0;
  Serial.begin(115200);
  
  //Initialization of the pins
  //Motor
  pinMode(motorState1Pin, INPUT);
  pinMode(motorState2Pin, INPUT);
  
  pinMode(motorInput1Pin, OUTPUT);
  pinMode(motorInput2Pin, OUTPUT);
  pinMode(motorInput3Pin, OUTPUT);
  pinMode(motorInput4Pin, OUTPUT);
  //DTA
  pinMode(tractionControlPin,OUTPUT); 
  pinMode(launchControlPin,OUTPUT); 
  pinMode(wetDryPin,OUTPUT); 
  pinMode(logDtaPin,OUTPUT); 
  pinMode(shiftCutPin, OUTPUT);
  //pinMode(LedPin, OUTPUT);
  pinMode(gearPotPin, OUTPUT);
  //Neutral sensor
  pinMode(neutralSensorPin, INPUT_PULLUP); 

  //Define interruptions
  attachInterrupt(paletteIncreasePin, Increase, RISING);
  attachInterrupt(paletteDecreasePin, Decrease, RISING);

  CAN.Transmit(engagedPosition-2, error,Auto);
  
  //Define Timer
  CANTimer.begin(Send_CAN, Can_send_period); //each period of the Timer the function Send_Can is launched

  //Initialization of the output
  //Motor, start with asking for homming position
  
  digitalWrite(motorInput1Pin, motorCommand[wantedPosition][0]);
  digitalWrite(motorInput2Pin, motorCommand[wantedPosition][1]);
  digitalWrite(motorInput3Pin, motorCommand[wantedPosition][2]);
  digitalWrite(motorInput4Pin, motorCommand[wantedPosition][3]);
  //DTA
  digitalWrite(shiftCutPin, HIGH);
  //digitalWrite(LedPin,LOW);
  digitalWrite(tractionControlPin,LOW); 
  digitalWrite(launchControlPin,LOW); 
  digitalWrite(wetDryPin,LOW); 
  digitalWrite(logDtaPin,LOW); 
  analogWrite(gearPotPin,0); 
  
  //We wait the end of the homming to start the void loop
  /*outMotor1 = digitalRead(motorState1Pin);
  outMotor2 = digitalRead(motorState2Pin);
  while (!PositionReachedOrHomingDone(outMotor1,outMotor2))
    {
         outMotor1 = digitalRead(motorState1Pin);
         outMotor2 = digitalRead(motorState2Pin);
    }
    engagedPosition = wantedPosition; 
    Serial.println("setup ok");
    Serial.println(engagedPosition);*/
}

void loop() 
{ 
  //MAJ of attributs by receiving the last datas
  CAN.Recieve();
  canStable++;
  canStable = min(canStable,Canstabledelay+1); //To be sure that the canStable variable will not exceed Arduino limite and go back to 0

  if(canStable > Canstabledelay) //If the CAN is stable then the info which are on it can be consider as reliable
  {
    digitalWrite(launchControlPin,CAN.getLaunchcontrolState()); //LAUNCH CONTROL
    digitalWrite(tractionControlPin,CAN.getTractionState()); //Traction control
    digitalWrite(wetDryPin,CAN.getWetdryState()); //WET DRY
    digitalWrite(logDtaPin,CAN.getLogState()); //LOG
    //Neutral
    if(CAN.getNeutralState()) 
    {
      Auto = false;
      wantedPosition = neutreCommand;
    }
    //Homming
    if(CAN.getHomingState()) 
    {
      Auto = false;
      wantedPosition = homingCommand;
    }  
  }

  //  //AUTO
  //Mode Auto turned ON when the first gear is engaged and the Decrease palette is pushed
  //it turned of on any command of the pilote on the palette or on the neutral and homming button
  if (Auto==true)
     {
      RPM=CAN.getRPM();
      if (millis()-T_ShiftAuto>500) {
        wantedPosition = CalculAuto(engagedPosition,RPM);
      }
      if (wantedPosition!=engagedPosition) {
        T_ShiftAuto = millis();
      }
     }

  //Motor mouvement
  move();
  
  //CAN transmission
  // error case : Motor is lost, motor still turning, motor NeedHomming 
  outMotor1 = digitalRead(motorState1Pin);
  outMotor2 = digitalRead(motorState2Pin);
  if ((MotorIsLost(outMotor1,outMotor2)) or (MotorIsTurning(outMotor1,outMotor2)) or (NeedHoming(outMotor1,outMotor2)))
      {
        error = 1;
      }
  else 
  { 
    engagedPosition=wantedPosition;
    if ((engagedPosition==neutreCommand) and (digitalRead(neutralSensorPin))) //There is a switch on neutral gear that put the neutral sensorPin on GND when gearbox is in neutral
      error=1; //If the switch is not down we have to signal an error
    else
      error=0; //If we are not in neutral we can't check and if we are in neutral and the switch is down it's OK
  }
  //DTA transmission 
  if (engagedPosition>=2)
    analogWrite(gearPotPin,valAnalog[engagedPosition-2]); // We send to the DTA the engaged gear with an analogique signal
}

void move()
{
  if (engagedPosition != wantedPosition)
  {
    //Send Command to the motor
    digitalWrite(motorInput1Pin, motorCommand[wantedPosition][0]);
    digitalWrite(motorInput2Pin, motorCommand[wantedPosition][1]);
    digitalWrite(motorInput3Pin, motorCommand[wantedPosition][2]);
    digitalWrite(motorInput4Pin, motorCommand[wantedPosition][3]);
    //Read output of the motor
    outMotor1 = digitalRead(motorState1Pin);
    outMotor2 = digitalRead(motorState2Pin);
    
    char flagQuitWhile = 0;
    
    while(MotorIsTurning(outMotor1,outMotor2)) //while the motor is turning
    { 
      delay(2);
      flagQuitWhile++;
      outMotor1 = digitalRead(motorState1Pin);
      outMotor2 = digitalRead(motorState2Pin);
      if (flagQuitWhile > 10)
      {  
        flagQuitWhile = 0;
        break;
      }    
    }
    if (PositionReachedOrHomingDone(outMotor1,outMotor2)) //We change the current speed only if we have reached the position
    {
      engagedPosition=wantedPosition; //We save the engaged position
    }
    digitalWrite(shiftCutPin, HIGH);//Open the injection
  }
}

void Increase() 
{
  static unsigned long T_Increase = 0;
  Serial.println("Increase interrupt");
  Serial.print("Out 1 : ");
  Serial.println(outMotor1);
  Serial.print("Out 2 : ");
  Serial.println(outMotor2);
  if ((millis() - T_Increase) > AntiReboundDelay)
  {
    Auto = false;
    // Si demande de Homming
    if (NeedHoming(outMotor1,outMotor2))
    {
      wantedPosition = 1; //On fait le homming
      T_Increase = millis();
    }
    else if(PassageVitesseIsPossible(engagedPosition+1)) 
    {
      wantedPosition = engagedPosition+1;
      T_Increase = millis();
     }
    else if (engagedPosition == 1)
     {  
      wantedPosition = engagedPosition+2;
      T_Increase = millis();
     }
     if (wantedPosition!=engagedPosition){
      digitalWrite(shiftCutPin, LOW);//Close the injection
      delay(IncreaseDelay);//Delay to let time for the motor
      Serial.print("Position engagée : ");
      Serial.println(engagedPosition);
      Serial.print("Position voulue : ");
      Serial.println(wantedPosition);
    move();
     }
  }
}

void Decrease() 
{
  static unsigned long T_Decrease = 0;
  Serial.println("Decrease interrupt");
  if ((millis() - T_Decrease) > AntiReboundDelay)
  {
    T_Decrease = millis();
    Auto = false;
    // Si demande de Homming
    if (NeedHoming(outMotor1,outMotor2))
    {
      wantedPosition = 1; //On fait le homming
    }
    else if(PassageVitesseIsPossible(engagedPosition-1)) 
    {
      wantedPosition = engagedPosition-1;
     }
    else if (engagedPosition == 3 and wantedPosition != engagedPosition-1)
    {
        if (Auto==false)
        {
          Auto = true;
        }
      }
    if (wantedPosition != engagedPosition)
    {
      digitalWrite(shiftCutPin, LOW);//Close the injection
      delay(DecreaseDelay);//Delay to let time for the motor
      move();
    }
  }
}

void Send_CAN()
{
  CAN.Transmit(engagedPosition-2, error,Auto);
}

int CalculAuto(int pos,int RPM){
  if (pos<=2) {
    return(3);
  }
  else if (pos==3 && RPM>RPM_shift[0]){
    return(4);
  }
  else if (pos==4 && RPM>RPM_shift[1]){
    return(5);
  }
  else if (pos==5 && RPM>RPM_shift[2]){
    return(6);
    }
  else {
    return(pos);
    }
}
