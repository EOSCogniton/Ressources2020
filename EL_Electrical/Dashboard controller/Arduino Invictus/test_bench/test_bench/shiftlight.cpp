/***************************************************************
  @file: shiftlight
  @author: Raphaël Viudès(RVS)
     for Ecurie Piston Sport Auto
      at Ecole Centrale de Lyon
  @description: countains all the functions that permit an update of
  the values displayed on the screen
  @functions: setShiftLight(int Pin, bool enable)
                Puts on the shift light at pin Pin if enable is True. Else turns off the shift light.
****************************************************************/
#include <Arduino.h>
/**************************************************************************/
//    Functions
/**************************************************************************/

void setShiftLight(int Pin,bool allum){
  if(allum){
    digitalWrite(Pin,HIGH);
  }
  else{
    digitalWrite(Pin,LOW);
  }
}

/***************************************************************************
  END FILE
***************************************************************************/
