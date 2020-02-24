// Libraries
#include "Accel.h"
#include "AutoX.h"
#include "End.h"
#include "Endur.h"
#include "SD_Card.h"
#include "SegDisp.h"
#include "Skid.h"

// Variables

int Sel; // Selector value

// Timer Variable

bool Start=0;
int Run=0;
bool Finish=0;

unsigned long Instant=0;
unsigned long Time=0;

// Function
void setup() {
    // Init Serial Port
    Serial.begin(9600);

    Serial.println("Init Begin");

    // Init 7 Seg
    Seg_Init();

    // Init SD Card
    SD_Card_Init();

    // Init Variables
    End();

    // Init Laser
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);

    Serial.println("Init Done");
}

void loop() {

    // Lecture selecteur
    Sel=analogRead(A6);

    Serial.println(Sel);

    if(Sel<=128){
        End();
        Accel();
    } if(128<Sel && Sel<=384){
        End();
        Skid();
    } if(384<Sel && Sel<=640){
        End();
        AutoX();
    } if(640<Sel && Sel<=896){
        End();
        Endur();
    }
}
