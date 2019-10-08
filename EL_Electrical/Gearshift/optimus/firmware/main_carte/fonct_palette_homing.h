/**************************************************************************/
/*!
    @file     fonct_palette_homing.h
    @author   Bruno Moreira Nabinger and Corentin Lepais (EPSA)
                                                  Ecurie Piston Sport Auto
    
    Contain the prototypes of the function for the palettes and the homing. 
    They are defined in the file fonct_palette_homing.cpp
 
    @section  HISTORY
    v0.1 - 17/10/2018 First release ()
*/
/**************************************************************************/

//Protection against multiple inclusions
#ifndef FONCT_PALETTE_HOMING_H
#define FONCT_PALETTE_HOMING_H


#include "Arduino.h"

boolean PassageVitesseIsPossible(int rapportEngager);
/**************************************************************************/
/*!
    @brief  Find if the changement of speed is possible
    @param[in] int rapportEngager
    @return    true - if (rapportEngager < 7 and rapportEngager > 2)
               false - otherwise
*/
/**************************************************************************/
 
#endif /* inclusion guards - FONCT_PALETTE_HOMING_H */

 
