// Libraries
#include "Accel.h"
#include "End.h"
#include "SD_Card.h"

/* Pinout
- Selector
  Pin A7
- SD Card Pinout
  Pin 4 : CS
  Pin 11 : MOSI
  Pin 12 : MISO
  Pin 13 : SCK
*/


// Variables

int Sel=0; // Selector value


// Function
void setup() {
    // Init Serial Port
    Serial.begin(9600);

    // Init SD Card
    SD_Card_Init();

    // Init des variables
    End();
}

void loop() {

    // On lit le selecteur
    Sel=analogRead(A7);

    if(Sel<=128) {
        Accel();
    } if(128<Sel && Sel<=384) {
        Skid();
    } if(384<Sel && Sel<=640) {
        AutoX();
    } if(640<Sel && Sel<=896) {
        Endur();
    }



    
}
