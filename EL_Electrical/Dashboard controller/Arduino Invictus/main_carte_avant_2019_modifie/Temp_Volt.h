#ifndef TEMP_VOLT_H
#define TEMP_VOLT_H



/**************************************************************************/
//    Inclusion of the necessary libraries and functions
/**************************************************************************/

#include <SPI.h>
#include "Adafruit_MCP23008.h"

extern Adafruit_MCP23008 mcp;



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/

extern const boolean PINS_R1[10][8];
extern const boolean PINS_R2[10][8];



/**************************************************************************/
//    Functions
/**************************************************************************/

void Seven_Seg_Calc(int Switch_Temp_Volt,int W_Temp,int Volts);
/*
    @brief      Seven_Seg_Calc calculates the numbers in the good units to
                send to TV_Update. It choose whether to calculate temperature
                or voltage as a function of the switch position.
    @param[in]  Switch_Temp_Volt
                W_Temp
                Volts
    @return     Calls TV_Update
*/

void TV_Update(int Microcontroller_Number,int Digit,int Point);
/*
    @brief      TV_Update recovers the number sent by Seven_seg_Calc and
                if in should illuminate the point or not. From PINS_R1
                and PINS_R2 it gets the pins of the microcontrollers
                (which are connected to the seven segments) must send
                current and which not. To understand the values of the
                constants, it is necessary to see how the microcontrollers
                and the segments are wired.
    @param[in]  Microcontroller_Number
                Digit
                Point
    @return     It uses a function given by the manufacturer of the
                microcontroller to tell if the n-connector pins should
                send current or not.
*/



#endif
