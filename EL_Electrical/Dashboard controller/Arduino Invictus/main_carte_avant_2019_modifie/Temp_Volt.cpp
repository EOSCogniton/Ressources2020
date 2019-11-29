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
//    Internal variables and constants used ONLY by the functions in this file
/**************************************************************************/

//0 turns on, 1 turns off
const boolean PINS_R1[10][8]={
  {1,0,0,0,0,0,0,0},  //0
  {1,0,1,1,1,1,0,0},  //1
  {0,1,0,0,1,0,0,0},  //2
  {0,0,0,1,1,0,0,0},  //3
  {0,0,1,1,0,1,0,0},  //4
  {0,0,0,1,0,0,1,0},  //5
  {0,0,0,0,0,0,1,0},  //6
  {1,0,1,1,1,0,0,0},  //7
  {0,0,0,0,0,0,0,0},  //8
  {0,0,0,1,0,0,0,0},  //9
// G C D E F A B PD     Pins of the 7 segments corresponding to the x1 (PD is the point of x10)
};
const boolean PINS_R2[10][8]{
  {0,0,0,0,1,0,0,0},  //0
  {0,1,0,1,1,0,1,1},  //1
  {0,0,0,1,0,1,0,0},  //2
  {0,0,0,1,0,0,0,1},  //3
  {0,1,0,0,0,0,1,1},  //4
  {1,0,0,0,0,0,0,1},  //5
  {1,0,0,0,0,0,0,0},  //6
  {0,0,0,1,1,0,1,1},  //7
  {0,0,0,0,0,0,0,0},  //8
  {0,0,0,0,0,0,0,1},  //9
// B A 1 F G C D E      Pins of the 7 segments corresponding to the x10 (1 is the 1 of the x100)
};

//


/**************************************************************************/
//    Functions
/**************************************************************************/
void Seven_Seg_Calc(int Switch_Temp_Volt,int W_Temp,int Volts){
    switch(Switch_Temp_Volt){
        case 0:                           //Water Temperature
            TV_Update(1,W_Temp%10,6);
            W_Temp=W_Temp/10;
            TV_Update(2,W_Temp,6);
            break;
        case 1:                           //Voltage
            TV_Update(1,Volts%10,7);
            Volts=Volts/10;
            TV_Update(2,Volts,7);
            break;
    }
}

void TV_Update(int Microcontroller_Number,int Digit,int Point){
  switch(Microcontroller_Number){
    case 1: //Numbers x1 + point (microcontroller 1)
        mcp.begin(1);
        for(int i=0;i<=Point;i++){
          mcp.pinMode(i,OUTPUT);
          mcp.digitalWrite(i,PINS_R1[Digit][i]);
        }
      break;
    case 2: //Numbers x10 + 1x100 (microcontroller 2)
        mcp.begin(2);
        if(Digit<=9){
          for(int i=0;i<=7;i++){
            if(i!=2){  //Jump colone 2 because it has the 1x100
              mcp.pinMode(i,OUTPUT);
              mcp.digitalWrite(i,PINS_R2[Digit][i]);
            }
          }
        }
        else{
          for(int i=0;i<=7;i++){
            mcp.pinMode(i,OUTPUT);
            mcp.digitalWrite(i,PINS_R2[Digit-10][i]);
          }
        }
      break;
  }
}



/***************************************************************************
  END FILE
***************************************************************************/
