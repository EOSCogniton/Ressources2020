// Libraries
#include "Accel.h"
#include "End.h"
#include "SD_Card.h"
#include "SegDisp.h"

/* Pinout
- Start Button
  Pin A0
- Detector LED
  Pin A1
- Selector
  Pin A7
- Signal Out
  Pin 2
  Pin 3
- Signal In
  Pin 5
  Pin 6
- SD Card Pinout
  Pin 4 : CS
  Pin 11 : MOSI
  Pin 12 : MISO
  Pin 13 : SCK
- 7 Seg Disp
  Pin 7  : CLK
  Pin 8  : DIO1
  Pin 9  : DIO2 
*/


// Variables

int Sel=0; // Selector value

// Timer Variable

bool Detection=0;
bool Start=0;
bool Finish=0;

unsigned long Instant=0;
unsigned long Time=0;


// Function
void setup() {
    // Init Serial Port
    Serial.begin(9600);

    // Init SD Card
    SD_Card_Init();

    // Init 7 Seg
    Seg_Init();

    // Init des variables
    End();

    Serial.println("  ");
}

void loop() {

    // Lecture selecteur
    Sel=analogRead(A7);

    if(Sel<=128){
        Accel();
    } if(128<Sel && Sel<=384) {
        // Skid();
    } if(384<Sel && Sel<=640) {
        // AutoX();
    } if(640<Sel && Sel<=896) {
        // Endur();
    }
}
