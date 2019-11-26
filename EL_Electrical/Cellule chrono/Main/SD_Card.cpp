// Libraries
#include "SD_Card.h"

// Variables

File TimingFile;

// Function

void SD_Card_Init() {

    // Init SD Card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
      Serial.println("Initialization failed!");
      while (1);
    }
    Serial.println("Initialization done.");

    SD_Card_Test();
}

void SD_Card_Test() {
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

void SD_Card_Write(int ID, String Time) {
    TimingFile = SD.open("Time.txt", FILE_WRITE);
    if(ID==1){
        TimingFile.print("Accel : ");
    } if(ID==2){
        TimingFile.print("Skid  : ");
    } if(ID==3){
        TimingFile.print("AutoX : ");
    } if(ID==4){
        TimingFile.print("Accel : ");
    }
    TimingFile.println("Time");
    TimingFile.close();
}
