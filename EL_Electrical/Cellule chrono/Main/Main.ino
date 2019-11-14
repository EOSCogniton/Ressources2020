// Libraries
#include "SD_Card.h"


// Pinout

// Selector
//        Pin A0

// SD Card Pinout
// CS   : Pin 4
// MOSI : Pin 11
// MISO : Pin 12
// SCK  : Pin 13


// Variables


// Function
void setup() {
    // Init Serial Port
    Serial.begin(9600);

    // Init SD Card
    SD_Card_Init();
}

void loop() {
}
