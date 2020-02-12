#ifndef SegDisp
#define SegDisp

// Libraries
#include "Arduino.h"
#include <TM1637Display.h> // https://github.com/avishorp/TM1637


// Functions

void Seg_Init();

void Seg_1_Write(int i);

void Seg_2_Write_Run();

void Seg_2_Write_Clear();

void Seg_2_Write_Num(unsigned long Time);

#endif
