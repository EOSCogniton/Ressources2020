/***************************************************************************
   
   Function name: Temp_Volt
   
   Author:        Martín Gómez-Valcárcel (MGV)
   
   Descriptions:  The functions in this file calculate and control the seven
                  segments that display water temperature or battery voltage.
                  Seven_Seg_Calc calculates the numbers in the good units to
                  send to TV_Update.
                  TV_Update recovers the number sent by Seven_seg_Calc and
                  if what it receives is temperature or voltage. That way it
                  knows whether or not to illuminate the point. From PINS_R1
                  and PINS_R2 it gets the pins of the microcontrollers
                  (which are connected to the seven segments) must send
                  current and which not.
                         
***************************************************************************/
#include "Temp_Volt.h"




/**************************************************************************/
//    Functions
/**************************************************************************/

void Seven_Seg_Calc(int Switch_Temp_Volt,int W_Temp,int Volts){
}

void TV_Update(int Microcontroller_Number,int Digit,int Point){
}



/***************************************************************************
  END FILE
***************************************************************************/
