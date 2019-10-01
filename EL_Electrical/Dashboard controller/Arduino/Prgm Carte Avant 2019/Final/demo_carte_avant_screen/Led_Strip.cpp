/***************************************************************************
   
   Function name: Led_Strip
   
   Author:        Martín Gómez-Valcárcel (MGV)
   
   Descriptions:  All these functions control the LED band. 
                  Engine_Failure checks, from certain values from the engine,
                  if there is a serious problem. If there is, it calls 
                  Led_Update to make all LEDs flash red.
                  Tachometer calculates from the limits set in RPM_MIN_MAX 
                  and the gear engaged, the number of LEDs to be lit and 
                  calls the Led_Update function to perform the task.
                  Led_Update receives the number of LEDs to illuminate, as
                  well as the gear the vehicle is in and if there is an 
                  engine fault. If there is a fault, all LEDs will flash
                  red. If the gear is equal to 0, then the LEDs will light
                  green. If the gear is equal to or greater than 1, up to 
                  5 LEDs will light green, 6 to 11 yellow, 12 to 16 red and
                  if they are 17 it will flash 5 times white, to inform the
                  pilot to increase the gear.
                         
***************************************************************************/
#include "Led_Strip.h"

/**************************************************************************/
//    Internal variables and constants used ONLY by the functions in this file
/**************************************************************************/
// Brightness
int Bright=15; // min=0, max=255


// Led constants
const int NUM_PIXELS = 16; // Defines the number of pixels in the strip
const int RPM_MIN_MAX[2][5] = {
  {    0, 9800, 9800, 9800, 9800},
  {12000,13500,12000,12000,12000}
}; // Matrix with the min/max rpm to change gear

// Led variables
int Led_Number;
int Rpm_Ratio;
int Rpm_Ratio_Corr;
int Blink_Time=200;
int Gear_Blink_Count=0;
int Gear_Blink_Led; // 0=off - 1=on
unsigned long Start_Fail_Millis;
unsigned long Current_Fail_Millis;
unsigned long Start_Gear_Millis;
unsigned long Current_Gear_Millis;

//Engine failure
int Fail_Init=0;
int Fail_Disp=0;

// Function to turn on the LEDs needed
// Strip.setPixelColor(index, green, red, blue);

// Led Strip Init
Adafruit_DotStar STRIP = Adafruit_DotStar(NUM_PIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

/**************************************************************************/
//    Functions
/**************************************************************************/

void Led_Init(){
    STRIP.begin();
    STRIP.show();
}

void Engine_Failure (signed W_Temp,signed A_Temp,signed O_Press){
    if(W_Temp>135 || A_Temp>60 || O_Press<1){
        if(Fail_Init==0){
            Start_Fail_Millis=millis();
            Fail_Disp=1;
            Fail_Init=1;
        }else{
            Current_Fail_Millis=millis();
            if(Current_Fail_Millis-Start_Fail_Millis>Blink_Time){
                Start_Fail_Millis=millis();
                Fail_Disp=abs(Fail_Disp-1);
                Serial.print("Ploum");
            }
        }
    }else{
        Fail_Disp=0;
        Fail_Init=0;
    }
}

void Tachometer (int Rpm,int Gear){
    Rpm_Ratio = (RPM_MIN_MAX[1][Gear]-RPM_MIN_MAX[0][Gear])/(NUM_PIXELS+1);
    Rpm_Ratio_Corr = Rpm-RPM_MIN_MAX[0][Gear];
    if(Rpm_Ratio_Corr>(NUM_PIXELS+1)*Rpm_Ratio){
        Led_Update(NUM_PIXELS+1,Gear,0);
    }
    else{
        for(int i=0 ; i<=NUM_PIXELS ; i++){
            if(i*Rpm_Ratio<=Rpm_Ratio_Corr && Rpm_Ratio_Corr<=(i+1)*Rpm_Ratio){
                Led_Update(i,Gear,0);
            }
        }
    }
}

void Led_Update (int Led_Number,int Gear,boolean Engine_Fail){
    
    Serial.print("\n");
    Serial.print("Fail_Disp = ");
    Serial.print(Fail_Disp);

    Serial.print("\n");
    Serial.print("Led_Disp = ");
    Serial.print(Led_Number);
    
    if(Gear>=1){
        // Shift Led Blink
        if(Led_Number==17){
            for(int i=0 ; i<NUM_PIXELS ; i++){
                STRIP.setPixelColor(i,255,255,255); 
            }
            STRIP.show();
            if(Gear_Blink_Count==0){
                Start_Gear_Millis=millis();
                Gear_Blink_Led=1;
                Gear_Blink_Count=1;
            }
            if(Gear_Blink_Count<=10){  //It's going to blink half the number writen
                Current_Gear_Millis=millis();
                if(Current_Gear_Millis-Start_Gear_Millis>Blink_Time){
                    Start_Gear_Millis=millis();
                    Gear_Blink_Led=abs(Gear_Blink_Led-1);
                    Gear_Blink_Count++;
                    if(Gear_Blink_Led==0){
                        STRIP.setBrightness(0);
                        Serial.print("Led Off");
                        STRIP.show();
                    }
                    else if(Gear_Blink_Led==1){
                        STRIP.setBrightness(Bright);
                        Serial.print("Led On");
                        STRIP.show();
                    }
                }
            }
        }
        else if(Fail_Disp==1){
            STRIP.setBrightness(Bright);
            Gear_Blink_Count=0;
            for(int i=0 ; i<NUM_PIXELS ; i++){
                STRIP.setPixelColor(i,0,255,0); 
            }
            STRIP.show();
        }
        else if(Led_Number>=12 && Led_Number<=16){
            STRIP.setBrightness(Bright);
            Gear_Blink_Count=0;
            for(int i=0 ; i<6 ; i++){
                if(i<=Led_Number){
                    STRIP.setPixelColor(i,255,0,0);
                }
                else{
                    STRIP.setPixelColor(i,0,0,0);
                }
            }
            for(int i=6 ; i<12 ; i++){
                if(i<=Led_Number){
                    STRIP.setPixelColor(i,255,255,0);
                }
                else{
                    STRIP.setPixelColor(i,0,0,0);
                }
            }
            for(int i=12 ; i<NUM_PIXELS ; i++){
                if(i<=Led_Number){
                    STRIP.setPixelColor(i,0,255,0);
                }
                else{
                    STRIP.setPixelColor(i,0,0,0);
                }
            }
        }
        else if(Led_Number>=6 && Led_Number<=11){
            STRIP.setBrightness(Bright);
            for(int i=0 ; i<6 ; i++){
                if(i<=Led_Number){
                    STRIP.setPixelColor(i,255,0,0);
                }
                else{
                    STRIP.setPixelColor(i,0,0,0);
                }
            }
            for(int i=6 ; i<NUM_PIXELS ; i++){
                if(i<=Led_Number){
                    STRIP.setPixelColor(i,255,255,0);
                }
                else{
                    STRIP.setPixelColor(i,0,0,0);
                }
            }
        }
        else if(Led_Number<=5){
            STRIP.setBrightness(Bright);
            Gear_Blink_Count=0;
            for(int i=0 ; i<NUM_PIXELS ; i++){
                if(i<=Led_Number){
                    STRIP.setPixelColor(i,255,0,0);
                }
                else{
                    STRIP.setPixelColor(i,0,0,0);
                }
            }
        }
        else if(Led_Number==0){
            STRIP.setBrightness(Bright);
            for(int i=0; i<NUM_PIXELS ; i++){
                STRIP.setPixelColor(i,0,0,0);
            }
        }
    }
    else if(Gear==0){
        STRIP.setBrightness(Bright);
        for(int i=0 ; i<NUM_PIXELS ; i++){
            if(i<=Led_Number){
                STRIP.setPixelColor(i,255,0,0);
            }
            else{
                STRIP.setPixelColor(i,0,0,0);
            }
        }
    }
    STRIP.show();

    //sprintf(Print, "RPM = %5d   Blink_Count = %2d   Blink_Led = %1d", Rpm, Blink_Count, Blink_Led);
    //Serial.print("\n");
    //Serial.print(Print);
}



/***************************************************************************
  END FILE
***************************************************************************/
