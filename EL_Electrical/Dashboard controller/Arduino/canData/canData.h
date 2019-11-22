#ifndef CANDATA_H
#define CANDATA_H

#include <FlexCAN.h>

// R_ID=0x1008
extern signed logRaceCap;

//R_ID=0x1100
extern signed ErrMotored;

// R_ID=0x2000
extern signed Rpm;
extern signed TPS; // %
extern signed W_Temp;
extern signed A_Temp;

// R_ID=0x2001
extern signed MAPKpa;
extern float Lambda; // x1000
extern float Kph; // x10
extern signed O_Press;

// R_ID=0x2002
extern signed F_Press;
extern signed O_Temp;
extern float Volts;// x10
extern float FuelConHR; // x10

// R_ID=0x2003

extern signed Gear;
extern float AdvanceDeg; //x10
extern float Inject; //x100
extern float FuelConKM; //x10

void receive();

void sendData();

#endif
