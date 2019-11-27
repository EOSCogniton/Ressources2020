#ifndef Acceleration
#define Acceleration

// Libraries
#include "Arduino.h"
#include "End.h"
#include "SD_Card.h"
#include "SegDisp.h"


// Variables

extern bool Detection;
extern bool Start;
extern bool Finish;

extern unsigned long Instant;
extern unsigned long Time;


// Functions

void Accel();

#endif
