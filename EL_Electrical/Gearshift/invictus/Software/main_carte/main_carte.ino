/**************************************************************************/
/*!
    @file     main_carte.cpp
    @author   Bruno Moreira Nabinger and Corentin Lepais (EPSA)
                                                  Ecurie Piston Sport Auto
    
    Main code for control the Motor with integrated Controller and CAN 
    interface BG 45 CI

 
    @section  HISTORY
    v0.6 - 06/04/2019 Add the sending of the speed to the DTA
    v0.5 - 13/02/2019 Modifications linked to the class CAN
    v0.4 - 06/02/2019 Add fonction to can_interface
    v0.3 - 10/11/2018 Comments of code and add of the file 
           "projectconfig.h", with the definitions of the pins numbers.
    v0.2 - 17/10/2018 Management of pallets and beginning of creations of 
                      the associated functions
    v0.1 - 10/10/2018 First release (previously code of Pedro)

    example of code version comment
    v0.2 - Rewrote driver for Adafruit_Sensor and Auto-Gain support, and
           added lux clipping check (returns 0 lux on sensor saturation)
*/
/**************************************************************************/
#include "projectconfig.h"

//Ajout des fonctions
#include "fonct_palette_homing.h"
#include "fonct_mot.h"
#include "can_interface.h"



//Definition of key-word
#define ERREUR -1 //Use to transmit that the motor is in error

//Definition of used variables 
boolean statePaletteIncrease; 
boolean statePaletteIncreaseBefore;
boolean statePaletteDecrease;
boolean statePaletteDecreaseBefore;

int positionEngager; // Contain what motor position is currently engaged
int wantedPosition;// Contain the motor position wanted so the speed rapport of the bike

boolean stateHoming; // Will contain the state of the homing button
boolean stateHomingBefore;

boolean outMotor1; //Info return by the motor
boolean outMotor2;//Info return by the motor

boolean stateNeutre;
boolean stateNeutreBefore;

boolean error;

const int neutrePosition = 2;
const int homingPosition=1;

boolean positionReached=true;

unsigned long T_D_Millis; //Containt the passed time

int valAnalog[9];

//Table which will contain the combination of the motor input for each speed
boolean motorPosition[9][4];//We use only 4 input motor to command it. The 5 is always 0

//Initialization of CANBUS
can_interface CAN;

void setup() 
{ 
  //Initialization of the pins
  pinMode(motorState1, INPUT);
  pinMode(motorState2, INPUT);

  pinMode(motorInput0, OUTPUT);
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
 
  pinMode(shiftCut, OUTPUT); 
  pinMode(gearPot, OUTPUT);

  pinMode(paletteIncrease, INPUT_PULLUP);  //  !! Il me semble qu'il y a deja des résistance de tirages sur le shield pour les pallettes !!__ARS
  pinMode(paletteDecrease, INPUT_PULLUP);  
  
  digitalWrite(motorInput0, LOW); // Initialisation de la position du moteur sur "Clear error and Stop" ¿Pourquoi? __ARS
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  
  
  digitalWrite(shiftCut, HIGH); //injection moteur

  //Initialization of the variables
  statePaletteIncreaseBefore = HIGH; //The pallets mode is INPUT_PULLUP, so the pin level is HIGH when it is inactive
  statePaletteDecreaseBefore = HIGH;
  positionEngager = 2;
  wantedPosition = 2;
  error = false;
  stateNeutreBefore=HIGH;
  
  
  T_D_Millis=millis();  //   time of last transmit 

  {//
    valAnalog[0]=0;
    valAnalog[1]=0;
    valAnalog[2]=43;
    valAnalog[3]=77;
    valAnalog[4]=110;
    valAnalog[5]=143;
    valAnalog[6]=176;
    valAnalog[7]=209;
    valAnalog[8]=242;
  }
  
  {//Initialization of the table. We use only the position 3-8, clear error and start Homing
    
    //Clear error and Stop
    motorPosition[0][0] = 0;
    motorPosition[0][1] = 0;
    motorPosition[0][2] = 0;
    motorPosition[0][3] = 0; 

    //Start Homing
    motorPosition[1][0] = 1;
    motorPosition[1][1] = 0;
    motorPosition[1][2] = 0;
    motorPosition[1][3] = 0;

    //Position 2: Neutre
    motorPosition[2][0] = 0;
    motorPosition[2][1] = 1;
    motorPosition[2][2] = 0;
    motorPosition[2][3] = 0;

    //Position 3 : vitesse 1
    motorPosition[3][0] = 1;
    motorPosition[3][1] = 1;
    motorPosition[3][2] = 0;
    motorPosition[3][3] = 0;

    //Position 4 : vitesse 2
    motorPosition[4][0] = 0;
    motorPosition[4][1] = 0;
    motorPosition[4][2] = 1;
    motorPosition[4][3] = 0;

    //Position 5 : vitesse 3
    motorPosition[5][0] = 1;
    motorPosition[5][1] = 0;
    motorPosition[5][2] = 1;
    motorPosition[5][3] = 0;

    //Position 6 : vitesse 4
    motorPosition[6][0] = 0;
    motorPosition[6][1] = 1;
    motorPosition[6][2] = 1;
    motorPosition[6][3] = 0;

    //Position 7 : vitesse 5
    motorPosition[7][0] = 1;
    motorPosition[7][1] = 1;
    motorPosition[7][2] = 1;
    motorPosition[7][3] = 0;

    //Position 8 : vitesse 6
    motorPosition[8][0] = 0;
    motorPosition[8][1] = 0;
    motorPosition[8][2] = 0;
    motorPosition[8][3] = 1;

    
  }

}

void loop() 
{ 
  CAN.Recieve();//MAJ of the can attributs by recieving the last data
  
  //Control of pallet+
  statePaletteIncrease = digitalRead(paletteIncrease);
  //If we only test if the state of the palette have changed or if we only test if the state is now 1, the test is going to be true 2 times:
  // when the pilot presses the palette and when it is released. We want to change the speed only  one time for each press

  //0 -> 1 = Detect the rising edge of signal statePaletteIncrease;
  if (statePaletteIncrease != statePaletteIncreaseBefore)// Check if state have changed
  {
    if (!statePaletteIncrease) // Check if state changed to 1, so we have the rising edge 0 -> 1 
    {
      if(PassageVitesseIsPossible(positionEngager)) 
      {
        
        wantedPosition = positionEngager+1;
      }
    }
    statePaletteIncreaseBefore = statePaletteIncrease;
  }
  
  //Control of pallet-
  statePaletteDecrease = digitalRead(paletteDecrease);
  //If we only test if the state of the palette have changed or if we only test if the state is now 1, the test is going to be true 2 times:
  // when the pilot presses the palette and when it is released. We want to change the speed only  one time for each press
  
  //0 -> 1 = Detect the rising edge of signal statePaletteDecrease;
  if (statePaletteDecrease != statePaletteDecreaseBefore)// Check if state have changed
  {
    if (!statePaletteDecrease) // Check if state changed to 1, so we have the rising edge 0 -> 1
    {
      if(PassageVitesseIsPossible(positionEngager))
      {
        
        wantedPosition = positionEngager-1;
      }
    }
    statePaletteIncreaseBefore = statePaletteIncrease;
  }

  
  //Gestion bouton homing
  stateHoming=CAN.getHomingState(); //We have the state of the homing thank to the can attribut
  if(stateHoming != stateHomingBefore)
  {
    if(!stateHoming)
    {
      wantedPosition=homingPosition;
    }
    stateHomingBefore = !stateHomingBefore;
  }



  if (wantedPosition!=positionEngager) //We try to change speed only if the pilot demands it
  {
    digitalWrite(shiftCut, LOW);//Close the injection
    EngageVitesse(wantedPosition);
    outMotor1 = digitalRead(motorState1);
    outMotor2 = digitalRead(motorState2);
    while(MotorIsTurning(outMotor1,outMotor2)) //while the motor is turning
    {
      outMotor1 = digitalRead(motorState1);
      outMotor2 = digitalRead(motorState2);
      positionReached=true; //We guess that we will reach the correct position
      if (MotorIsLost(outMotor1,outMotor2)) //error
      {
        //We clean the error
        EngageVitesse(0); //the motor stop
        //We transmit the error to the CAN
        while(!CAN.Transmit(ERREUR, T_D_Millis)) 
        {
          //We try to transmit the error until the transmission is good
        }
        T_D_Millis=millis(); // We save the time of last transmit
        positionReached=false;
      }
    }


    
    if (positionReached) //We change the current speed only if we have reached the position
    {
      positionEngager=wantedPosition; //We save the engaged position
    }
    digitalWrite(shiftCut, HIGH);//Open the injection
  }
  
  if (CAN.Transmit(positionEngager-2, T_D_Millis)); //We sent the engaged speed to the CAN (Speed= PositionEngager-2)
  {
     T_D_Millis=millis(); // We save the time of last transmit
     TransmetToDTATheGear(positionEngager-2); // We send to the DTA the engaged gear
  }
}

void EngageVitesse(int wantedPosition) //Function which pass the speed
{
  digitalWrite(motorInput0, motorPosition[wantedPosition][0]);
  digitalWrite(motorInput1, motorPosition[wantedPosition][1]);
  digitalWrite(motorInput2, motorPosition[wantedPosition][2]);
  digitalWrite(motorInput3, motorPosition[wantedPosition][3]);
}

void TransmetToDTATheGear(int rapportEngager){analogWrite(gearPot,valAnalog[rapportEngager]);}
