#ifndef SD_Card
#define SD_Card

// Libraries
#include <SPI.h>
#include <SD.h>

// Functions

void SD_Card_Init();

void SD_Card_Test();

void SD_Card_Write(int ID, String Time);

#endif
