#include <TM1637Display.h>

int CLK=8;
int DIO=10;

TM1637Display display = TM1637Display(CLK, DIO);

const uint8_t done[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,           // D
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,           // O
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F,                   // N
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G                    // E
};

void setup() {
  // put your setup code here, to run once:

  display.clear();
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  display.setBrightness(7);

  delay(1000);

  int i;
  for (i = 900; i < 1101; i++) {
    display.showNumberDec(i);
    delay(10);
  }

  delay(1000);

  display.setSegments(done);

  delay(1000);
}
