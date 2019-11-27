#ifndef GEAR_UPDATE_H
#define GEAR_UPDATE_H



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/

#include <SPI.h>
#include "Adafruit_MCP23008.h"



/**************************************************************************/
//    External variables and constants used by the functions in this file
/**************************************************************************/

extern Adafruit_MCP23008 mcp;
extern const boolean PINS_GEAR[7][7];



/**************************************************************************/
//    Functions
/**************************************************************************/
void Gear_Init();

void Gear_Update(signed Gear, signed Error);
/*
    @brief      Grear_Update receives the gear the engine is in and, from
                PINS_GEAR, determines which segments it has to illuminate
                so that the pilot knows the gear he's in.
    @param[in]  Gear
    @return     It uses a function given by the manufacturer of the
                microcontroller to tell if the n-connector pins should
                send current or not.
*/



#endif
