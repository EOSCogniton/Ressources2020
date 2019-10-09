// Libraries
#include "LedStrip.h"

// Pin Out

// Yellow : GND   : GND
// Green  : DATA  : D7
// Blue   : CLOCK : D8 
// Purple : 5V    : 5V

const int DT_L = 7;
const int CLK_L = 8;

// Led Strip Init

Adafruit_DotStar STRIP = Adafruit_DotStar(15, DT_L, CLK_L, DOTSTAR_BRG); // Number of LEDs = 15

// Functions

void LedStrip_Init(){
    // Init
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
        clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
    #endif
    
    STRIP.setBrightness(20); // Brightness = 20 / 255
    STRIP.begin(); // Initialize pins for output
    STRIP.show();  // Turn all LEDs off 
}

void MAJ_Led(String Data){
    // Color code : G,R,B

    // Init Variables
    String Mode=Data.substring(4,5);
    String Rpm=Data.substring(6,7);
    String Shift=Data.substring(0,3);

    // Init : Shutdown all LEDs    
    for (int i=0 ; i<15 ; i++){
        STRIP.setPixelColor(i,0,0,0); 
    }

    // Mode
    int Mode_Led=1; // A modifier
    STRIP.setPixelColor(Mode_Led,255,0,0);

    // RPM
    if (Rpm=="1"){
        STRIP.setPixelColor(5,0,255,0); 
    } else if (Rpm=="2"){
        STRIP.setPixelColor(5,0,255,0); 
        STRIP.setPixelColor(6,0,255,0); 
    } else if (Rpm=="3"){
        STRIP.setPixelColor(5,0,255,0); 
        STRIP.setPixelColor(6,0,255,0); 
        STRIP.setPixelColor(7,0,255,0); 
    } else if (Rpm=="4"){
        STRIP.setPixelColor(5,0,255,0); 
        STRIP.setPixelColor(6,0,255,0); 
        STRIP.setPixelColor(7,0,255,0); 
        STRIP.setPixelColor(8,0,255,0); 
    } else if (Rpm=="5"){
        STRIP.setPixelColor(5,0,255,0); 
        STRIP.setPixelColor(6,0,255,0); 
        STRIP.setPixelColor(7,0,255,0); 
        STRIP.setPixelColor(8,0,255,0); 
        STRIP.setPixelColor(9,0,255,0); 
    }

    // Shift
    if (Shift=="100"){
        for(int i=10 ; i<15 ; i++){
            STRIP.setPixelColor(i,0,0,255); 
        }
    }

    // Display
    STRIP.show();   
}
