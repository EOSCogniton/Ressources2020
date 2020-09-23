/**************************************************************************/
/*!
    @file     fonct_mot.cpp
    @author   Bruno Moreira Nabinger and Corentin Lepais (EPSA)
                                                  Ecurie Piston Sport Auto
    
    The functions manage the informations issued from the motor 

 
    @section  HISTORY
    V0.2 - 01/11/2018 the functions motorIsLost, motorIsArrested and 
           motorIsturning wrote
    v0.1 - 17/10/2018 First release ()
*/
/**************************************************************************/
#include "fonct_mot.h"


boolean MotorIsLost(boolean OUT1, boolean OUT2) //Indicate if the motor is in error
{
  if (OUT1==0 and OUT2==0)
  {
    return true;
  }
  return false;
}

boolean NoHoming(boolean OUT1, boolean OUT2) //Indicate if there is no homing
{
  if (OUT1==0 and OUT2==1)
  {
    return true;
  }
  return false;
}

boolean MotorIsTurning(boolean OUT1, boolean OUT2)// Indicate if the motor is turning
{
  if (OUT1==1 and OUT2==1)
  {
    return true;
  }
  return false;
}

boolean PositionReachedOrHomingDone(boolean OUT1, boolean OUT2)
{
  if (OUT1==1 and OUT2==0)
  {
    return true;
  }
  return false;  
}


boolean NeedHoming(boolean OUT1, boolean OUT2)
{
  if (OUT1==0 and OUT2==1)
  {
    return true;
  }
  return false;  
}
