/**************************************************************************/
/*!
    @file     fonct_palette_homing.cpp
    @author   Bruno Moreira Nabinger and Corentin Lepais (EPSA)
                                                  Ecurie Piston Sport Auto
    
    The functions manage the informations issued from the pallet

 
    @section  HISTORY
    v0.2 - 06/04/2019 Function TransmetToDTAGear
    v0.1 - 17/10/2018 First release ()
*/
/**************************************************************************/


#include "fonct_palette_homing.h" //Header contenant les prototypes
#include "projectconfig.h" 

boolean PassageVitesseIsPossible(int rapportEngager)
{
  //On passe le rapport supérieur que si le rapport engagé est inférieur ou égale à 6
  //On passe le rapport inférieur que si le rapport engagé est supérieur ou égale à 3 
  if(rapportEngager<7 and rapportEngager>2) 
  {
    return true;
  }
  else
  {
    return false;
  }
}
