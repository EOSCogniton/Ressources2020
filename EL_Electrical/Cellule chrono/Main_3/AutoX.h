#ifndef Autocross
#define Autocross

// Libraries
#include "Arduino.h"
#include "End.h"
#include "SD_Card.h"
#include "SegDisp.h"

// Variables

extern bool Start;
extern int Run;
extern bool Finish;

extern unsigned long Instant;
extern unsigned long Time;

// Functions

void AutoX();

#endif
