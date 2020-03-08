#ifndef SegDisp
#define SegDisp

// Libraries
#include "Arduino.h"
#include "SevenSegmentTM1637.h"


// Functions

void Seg_Init();

void Seg_1_Write(int i);

void Seg_2_Write_Run();

void Seg_2_Write_Clear();

void Seg_2_Write_Num(unsigned long Time);

#endif
