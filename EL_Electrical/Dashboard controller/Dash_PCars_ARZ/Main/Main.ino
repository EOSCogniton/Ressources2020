// Libraries
#include "Comm_PC.h"
#include "Encoder.h"
#include "LedStrip.h"
#include "Nextion.h"
#include <SoftwareSerial.h>

// Functions

// Setup
void setup() {
    // PC Serial
    Serial.begin(115200);
    Serial.println("Serial Ready");
    delay(200);
  
    // Nextion Serial
    Nextion_Init();

    // Encoder Init
    Encoder_Init();

    // LedStrip
    LedStrip_Init();
    
    // Led_13
    pinMode(13, OUTPUT);
    delay(200);
}

// Loop
void loop() {
    // Comm_PC
    MAJ_Data();

    // Encoder
    Button();
    Rotary();
}
