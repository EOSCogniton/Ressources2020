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

// Led constants
const int Bright=20;
const int NUM_PIXELS = 16; // Defines the number of pixels in the strip
const double RPM_MIN_MAX[2][7] = {
  {    0, 2000, 2000, 2000, 2000, 2000, 2000},
  {14000,13300,13100,12900,12800,12700,12000}
}; // Matrix with the min/max rpm to change gear

// Led variables
int Led_Number;
int Led_Number_B;
double Rpm_Ratio;
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
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif
  STRIP.setBrightness(Bright);
  STRIP.begin(); // Initialize pins for output
  STRIP.show();  // Turn all LEDs off ASAP
}

void Engine_Failure (signed W_Temp,signed A_Temp,signed O_Press){
    if(W_Temp>110 || A_Temp>60 || O_Press<1){
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

void Tachometer (double Rpm,int Gear,bool Auto){
    Serial.print("\n");
    Serial.println(Rpm);
    Serial.print("\n");
    Serial.println(RPM_MIN_MAX[0][Gear]);
    Serial.print("\n");
    Serial.println((RPM_MIN_MAX[1][Gear]));
    Serial.print("\n");
    Serial.println(NUM_PIXELS+1);
    if (Rpm>RPM_MIN_MAX[0][Gear]) {
      Rpm_Ratio = ((Rpm-RPM_MIN_MAX[0][Gear])/(RPM_MIN_MAX[1][Gear]-RPM_MIN_MAX[0][Gear])*(NUM_PIXELS+1)); ;
    }
    else {
      Rpm_Ratio = 0;
      }
    Serial.print("\n");
    Serial.println(Rpm_Ratio);
    Serial.print("\n");
    Serial.println(Gear);
    if (Rpm_Ratio > (NUM_PIXELS+1)) {
      Rpm_Ratio =  NUM_PIXELS+1;         
    }
    Led_Update (Rpm_Ratio,Gear,Auto);
}

void Led_Update (int Led_Number,int Gear,bool Auto){
    
    //Serial.print("\n");
    //Serial.print("Fail_Disp = ");
    //Serial.print(Fail_Disp);

    //Serial.print("\n");
    //Serial.print("Led_Disp = ");
    //Serial.print(Led_Number);
    if(Gear==0){
        STRIP.fill(0x00FFFFFF,0, Led_Number); //On allume en blanc les LED en dessous de LED Number
        STRIP.fill(0x00000000,Led_Number,NUM_PIXELS); //on éteint les autres
    }
    else if(Gear>0){
          if (Led_Number<10){
            STRIP.fill(0x00FF0000,0, Led_Number); //on allume les LED en vert
            STRIP.fill(0x00000000,Led_Number,NUM_PIXELS); //on éteint les autres
          }
          else if (Led_Number<15)   {        // En jaune
            STRIP.fill(0x00FF0000,0, 10); //on allume les LED en vert jusqu'a la dixième
            STRIP.fill(0x00FFFF00,10, Led_Number); //on allume entre 10 et LED_number en jaune
            STRIP.fill(0x00000000,Led_Number,NUM_PIXELS); //on éteint les autres
          }
          else {                            
            STRIP.fill(0x00FF0000,0, 10); //on allume les LED en vert jusqu'a la dixième
            STRIP.fill(0x00FFFF00,10, 15); //on allume entre 10 et 15 en jaune
            STRIP.fill(0x0000FF00,15, Led_Number); //on allume entre 15 et LED_Number en rouge
            STRIP.fill(0x00000000,Led_Number,NUM_PIXELS); //on éteint les autres
          }
        }


    // Affichage d'une erreur
    if(Fail_Disp==1){
        Gear_Blink_Count=0;
        STRIP.fill(0x00FF0000,0,NUM_PIXELS); 
    }

    // Clignotement du bandeau = Shift Light
    if (Led_Number<17) {Gear_Blink_Count=0;}
    if(Led_Number==17){
        STRIP.fill(0x00FFFFFF,0,NUM_PIXELS); 
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
                   //Serial.print("Led Off");
                }
                else if(Gear_Blink_Led==1){
                    STRIP.setBrightness(Bright);
                    //Serial.print("Led On");
                }
            }
        }
    }
    
    if (Auto){
      Serial.print("\n");
      Serial.print("Auto");
      STRIP.fill(0x00FF00FF,0,6); 
    }
   STRIP.show();
}

/***************************************************************************
  END FILE
***************************************************************************/
