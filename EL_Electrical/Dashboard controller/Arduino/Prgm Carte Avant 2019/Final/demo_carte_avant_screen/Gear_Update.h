#ifndef GEAR_UPDATE_H
#define GEAR_UPDATE_H



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/



/**************************************************************************/
//    External variables and constants used by the functions in this file
/**************************************************************************/



/**************************************************************************/
//    Functions
/**************************************************************************/
void Gear_Init();

void Gear_Update(signed Gear);
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
