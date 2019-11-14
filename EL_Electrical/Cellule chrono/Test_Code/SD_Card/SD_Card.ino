#include <SPI.h>
#include <SD.h>

// SD Card Pinout
// CS   : Pin 4
// MOSI : Pin 11
// MISO : Pin 12
// SCK  : Pin 13



// Variables
// SD Card
File TimingFile;

void setup() {
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
    TimingFile = SD.open("Time.txt", FILE_WRITE);
    TimingFile.println("Time");
    TimingFile.close();
    delay(1000);




    
}
