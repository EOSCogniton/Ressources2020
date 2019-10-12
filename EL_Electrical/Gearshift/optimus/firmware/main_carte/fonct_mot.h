/**************************************************************************/
/*!
    @file     fonct_mot.h
    @author   Bruno Moreira Nabinger and Corentin Lepais (EPSA)
                                                  Ecurie Piston Sport Auto
    
    Contain the prototypes of the function that manage the information 
    issued from the motor. They are defined in the file fonct_mot.cpp

 
    @section  HISTORY
    V0.2 - 01/11/2018 the functions motorIsLost, motorIsArrested and
           motorIsturning wrote
    v0.1 - 17/10/2018 First release ()
*/
/**************************************************************************/

//Protection against multiple inclusions
#ifndef FONCT_MOT_H
#define FONCT_MOT_H

#include "Arduino.h"

/**************************************************************************/
/*!
    @brief  Indicate if the motor is in a error state (Status = Error)
    @param[in] boolean motorState0
    @param[in] boolean motorState1
    @return    true - if (motorState0 == 0  AND motorState1 == 0)
               false - otherwise
    @section EXAMPLE
    @code
    boolean error;
    // Read Motor State pins
    outMotor1 = digitalRead(motorState1);
    outMotor2 = digitalRead(motorState2);
    if (MotorIsLost(outMotor1, outMotor2))
    {  error = true;
    }
    @endcode
*/
/**************************************************************************/
boolean MotorIsLost(boolean OUT1, boolean OUT2);

/**************************************************************************/
/*!
    @brief  Indicate if there is no homing
    (Status = [motorState0 motorState1]
              [0 1] No homing )
    @param[in] boolean motorState0
    @param[in] boolean motorState1
    @return    true - if (motorState0 == 0  AND motorState1 == 1)   
               false - otherwise
*/
/**************************************************************************/
boolean NoHoming(boolean OUT1, boolean OUT2);

/**************************************************************************/
/*!
    @brief  Indicate if the motor is turning (Status = Moving)
    @param[in] boolean motorState0
    @param[in] boolean motorState1
    @return    true - if (motorState0 == 1  AND motorState1 == 1)     
               false - otherwise
*/
/**************************************************************************/
boolean MotorIsTurning(boolean OUT1, boolean OUT2);

/**************************************************************************/
/*!
    @brief  Indicate if the wanted position is reached or if the homing is done (depend of the motor command)
    @param[in] boolean motorState0
    @param[in] boolean motorState1
    @return    true - if (motorState0 == 1  AND motorState1 == 0)     
               false - otherwise
*/
/**************************************************************************/
boolean PositionReachedOrHomingDone(boolean OUT1, boolean OUT2);
#endif /* inclusion guards - FONCT_MOT_H */
