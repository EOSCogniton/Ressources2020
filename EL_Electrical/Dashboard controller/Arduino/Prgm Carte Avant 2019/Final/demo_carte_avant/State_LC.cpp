/***************************************************************************
  
   Function name: State_LC
   
   Author:        Arthur Rodríguez (ARZ)
   
   Descriptions:  Exhaustive description of what all the functions in this 
                  file do and how they interact with each other.
                            
***************************************************************************/
#include "State_LC.h"



/**************************************************************************/
//    Internal variables and constants used ONLY by the functions in this file
/**************************************************************************/

// Launch Control
int Switch_LC=0;
int Limit_LC=30; // Max LC Speed
bool Led_LC = 0;



/**************************************************************************/
//    Functions
/**************************************************************************/

void State_LC(int Kph){

    Switch_LC=digitalRead(LC_SWITCH_PIN); 
  
    //sprintf(Print, "Switch_LC = %1d   KPH = %3d   Led_LC = %1d", Switch_LC, Kph, Led_LC);
    //Serial.print("\n");
    //Serial.print(Print);
    
    if(Switch_LC==1 && Kph<Limit_LC){
        Led_LC=1;
        digitalWrite(LC_LED_PIN,LOW);
    }
    if(Kph>Limit_LC){
        Led_LC=0;
        digitalWrite(LC_LED_PIN,LOW);
    }
}



/***************************************************************************
  END FILE
***************************************************************************/
