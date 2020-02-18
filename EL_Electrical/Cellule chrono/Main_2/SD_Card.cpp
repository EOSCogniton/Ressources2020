// Libraries
#include "SD_Card.h"

// Variables

File TimingFile;

// Function

void SD_Card_Init(){

    // Init SD Card
    Serial.println("Init SD Card...");
    if (!SD.begin(4)) {
      Serial.println("Init SD Card Failed!");
      while (1);
    }

    SD_Card_Test();
    Serial.println("Init SD Card Done");
}

void SD_Card_Test(){    
    TimingFile = SD.open("Time.txt", FILE_WRITE);
    if (TimingFile) {
        TimingFile.println("\n Invictus Timing \n");
        TimingFile.close();
    }
  
    // Reading Test
    Serial.println("Init SD Card : Reading Test");
    
    TimingFile = SD.open("Time.txt");
    if (TimingFile){
        TimingFile.close();
    }
}

void SD_Card_Write(int ID, unsigned long Time, unsigned long Time1=0, unsigned long Time2=0) {
    TimingFile = SD.open("Time.txt", FILE_WRITE);
    if(ID==1){
        TimingFile.print("Accel,");
        TimingFile.print(Time);
    }
    if(ID==2){ // Tps total, tps tour 1, tps tour 2
        TimingFile.print("Skid,");
        TimingFile.print(Time);
        TimingFile.print(",");
        TimingFile.print(Time1);
        TimingFile.print(",");
        TimingFile.print(Time2);
    } 
    if(ID==3){
        TimingFile.print("AutoX,");
        TimingFile.print(Time);
    } 
    if(ID==4){
        TimingFile.print("Accel,");
    }
    TimingFile.println(",ms");
    TimingFile.close();
}
