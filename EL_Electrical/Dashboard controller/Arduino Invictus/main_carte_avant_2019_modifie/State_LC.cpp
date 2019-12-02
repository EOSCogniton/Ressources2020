/***************************************************************************
  
   Function name: State_LC
   
   Author:        Arthur Rodríguez (ARZ)
   
   Descriptions:  Exhaustive description of what all the functions in this 
                  file do and how they interact with each other.
                            
***************************************************************************/
#include "State_LC.h"

/**************************************************************************/
//    Functions
/**************************************************************************/

void State_LC(bool Led_LC){
    if(Led_LC==1){
        digitalWrite(LC_LED_PIN,HIGH);
    }
}

/***************************************************************************
  END FILE
***************************************************************************/
