#include <TM1637Display.h>

int CLK=7;
int DIO1=8;
int DIO2=9;

TM1637Display display1 = TM1637Display(CLK, DIO1);
TM1637Display display2 = TM1637Display(CLK, DIO2);

const uint8_t Done[] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // D
    SEG_C | SEG_D | SEG_E | SEG_G,                   // o
    SEG_C | SEG_E | SEG_G,                           // n
    SEG_D | SEG_E | SEG_G                            // e
};

const uint8_t Strt[] = {
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // S
    SEG_E | SEG_F | SEG_G,                           // t
    SEG_E | SEG_G,                                   // r
    SEG_E | SEG_F | SEG_G,                           // t
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

void setup() {
  // put your setup code here, to run once:

  display1.clear();
  display2.clear();
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  display1.setBrightness(7);
  display2.setBrightness(7);

  int i;
  for (i = 900; i < 1100; i++) {
    display1.showNumberDec(i);
    delay(10);
  }

  delay(2000);
  display1.setSegments(Acc);
  display2.setSegments(Run);
  delay(2000);
  display1.setSegments(Skid);
  delay(2000);
  display1.setSegments(AutX);
  display2.setSegments(End);
  delay(2000);
  display1.setSegments(Strt);
  delay(2000);
  display1.setSegments(Done);
  delay(2000);
}
