// Libraries
#include "SegDisp.h"

// Pinout
const int CLK=8;
const int DIO1=9;
const int DIO2=10;

// Variables

const uint8_t Strt[] = {
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // S
    SEG_E | SEG_F | SEG_G,                           // t
    SEG_E | SEG_G,                                   // r
    SEG_E | SEG_F | SEG_G,                           // t
};

const uint8_t Done[] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // D
    SEG_C | SEG_D | SEG_E | SEG_G,                   // o
    SEG_C | SEG_E | SEG_G,                           // n
    SEG_D | SEG_E | SEG_G                            // e
};

const uint8_t Run[] = {                              // 
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // R
    SEG_C | SEG_D | SEG_E,                           // u
    SEG_C | SEG_E | SEG_G,                           // n
    0x00
};

const uint8_t Acc[] = {                              // 
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
    SEG_D | SEG_E | SEG_G,                           // c
    SEG_D | SEG_E | SEG_G,                           // c
    0x00
};

const uint8_t Skid[] = {
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // S
    SEG_C | SEG_E | SEG_F | SEG_G,                   // k
    SEG_E,                                           // i
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G            // d
};

const uint8_t AutX[] = {
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
    SEG_C | SEG_D | SEG_E,                           // u
    SEG_E | SEG_F | SEG_G,                           // t
    SEG_B | SEG_C | SEG_E | SEG_F | SEG_G            // X
};

const uint8_t End[] = {                              // 
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
    SEG_C | SEG_E | SEG_G,                           // n
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
    0x00
};

// Function

// Display
TM1637Display Disp1 = TM1637Display(CLK, DIO1);
TM1637Display Disp2 = TM1637Display(CLK, DIO2);

void Seg_Init() {
    // Display 1 
    Disp1.clear();
    Disp1.setBrightness(7);

    // Display 2
    Disp2.clear();
    Disp2.setBrightness(7);
}

void Seg_1_Write() {
    
}

void Seg_2_Write(unsigned long Num) {
    Disp1.showNumberDec(Num);
}
