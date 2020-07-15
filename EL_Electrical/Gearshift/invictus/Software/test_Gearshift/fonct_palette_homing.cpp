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

boolean PassageVitesseIsPossible(int positionEngagee)
{
  //On passe le rapport supérieur que si la vitesse est inférieur ou égale à 5 --> position 7 minimum
  //On passe le rapport inférieur que si la vitesse est supérieur ou égale à 1 --> position 3 minimum
  if(positionEngagee<8 and positionEngagee>2) 
  {
    return true;
  }
  else
  {
    return false;
  }
}
