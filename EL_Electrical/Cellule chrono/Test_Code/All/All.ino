#include <TM1637Display.h>
#include <SPI.h>
#include <SD.h>

int CLK=7;
int DIO1=8;
int DIO2=9;

bool val;


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


File TimingFile;

int Number=12;


void setup() {
    // put your setup code here, to run once:
  
    display1.clear();
    display2.clear();
    delay(1000);

    // Init Serial Port
    Serial.begin(9600);
  
    // Init SD Card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
      Serial.println("Initialization failed!");
      while (1);
    }
    Serial.println("Initialization done.");

    test();

    pinMode(2, OUTPUT);
    pinMode(5, INPUT);
    pinMode(A0, INPUT_PULLUP);
}
void test() {
    // Write Test
    Serial.println("SD Card : Writing Test");
    
    TimingFile = SD.open("Time.txt", FILE_WRITE);
    if (TimingFile) {
        TimingFile.println("Invictus Timing");
        TimingFile.close();
        Serial.println("Writing Test Done");
    } else {
        Serial.println("Writing Test Failed");
    }
  
    // Reading Test
    Serial.println("SD Card : Reading Test");
    
    TimingFile = SD.open("Time.txt");
    if (TimingFile) {
        TimingFile.close();
        Serial.println("Reading Test Done");
    } else {
        // if the file didn't open, print an error:
        Serial.println("Reading Test Failed");
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    display1.setBrightness(7);
    display2.setBrightness(7);
  
    Serial.println("Start");
  
    int i;
    for (i = 980; i < 1020; i++) {
        display2.showNumberDec(i);
        delay(10);
    }
  
    delay(500);
    val=1-digitalRead(A0);
    Serial.print(val);
    display1.setSegments(Strt);
    digitalWrite(2, HIGH);
    val=digitalRead(5);
    Serial.print(val);
    delay(500);
    display2.setSegments(Strt);
    delay(500);
    display1.setSegments(Done);
    digitalWrite(2, LOW);
    delay(500);
    val=digitalRead(5);
    Serial.print(val);
    
    TimingFile = SD.open("Time.txt", FILE_WRITE);
    TimingFile.println(Number);
    // Serial.println(Number);
    TimingFile.close();
    delay(500);
  
    Number++;
}
