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
#include "projectconfig.h" // ¿¿Importation redondante?? __ARS

boolean PassageVitesseIsPossible(int rapportEngager)  //cette fonction me semble pas ok __ARS
{
  //On passe le rapport supérieur que si le rapport engagé est inférieur ou égale à 8
  //On passe le rapport inférieur que si le rapport engagé est supérieur ou égale à 3 

  //return (rapportEngager<9 and rapportEngager>2); __ARS

  if(rapportEngager<9 and rapportEngager>2) 
  {
    return true;
  }
  else
  {
    return false;
  }
}
