// Libraries
#include "SegDisp.h"

// Variables

const uint8_t Acc[] = {                              // 
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
    SEG_D | SEG_E | SEG_G,                           // c
    SEG_D | SEG_E | SEG_G,                           // c
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
};

// Function

// Display
// TM1637Display Disp1 = TM1637Display(CLK, DIO);
// TM1637Display Disp2 = TM1637Display(CLK, DIO);

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
