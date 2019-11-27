#ifndef LED_STRIP_H
#define LED_STRIP_H



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/

#include <Adafruit_DotStar.h>
#include "projectconfig.h"



/**************************************************************************/
//    External variables and constants used by the functions in this file
/**************************************************************************/

extern signed Rpm;
extern signed Gear;
extern signed W_Temp;
extern signed A_Temp;
extern signed O_Press;
extern signed Auto;



/**************************************************************************/
//    Functions
/**************************************************************************/

void Led_Init();

void Engine_Failure (signed W_Temp,signed A_Temp,signed O_Press);
/*
    @brief      Engine_Failure checks, from certain values from the engine,
                if there is a serious problem. If there is, it calls 
                Led_Update to make all LEDs flash red.
    @param[in]  W_Temp
                A_Temp
                O_Press
    @return     Calls Led_Update.
*/

void Tachometer (double Rpm,int Gear,bool Auto);
/*
    @brief      Tachometer calculates from the limits set in RPM_MIN_MAX 
                and the gear engaged, the number of LEDs to be lit and 
                calls the Led_Update function to perform the task.
    @param[in]  Rpm
                Gear
    @return     Calls Led_Update.
*/

void Led_Update (int Led_Number,int Gear,bool Auto);
/*
    @brief      Led_Update receives the number of LEDs to illuminate, as
                well as the gear the vehicle is in and if there is an 
                engine fault. If there is a fault, all LEDs will flash
                red. If the gear is equal to 0, then the LEDs will light
                green. If the gear is equal to or greater than 1, up to 
                5 LEDs will light green, 6 to 11 yellow, 12 to 16 red and
                if they are 17 it will flash 5 times white, to inform the
                pilot to increase the gear.
    @param[in]  Led_Number
                Gear
                Engime_Fail
    @return     Calls a function provided by the manufacturer of the LED
                strip.
                Strip.setPixelColor(index,green,red,blue)
*/



#endif
