#ifndef PROJECTCONFIG_H //if not define symbol PROJECTCONFIG_H
#define PROJECTCONFIG_H

/**************************************************************************/

//                        IMPORTANT !!!!!!


//           Make sure that the definitions in this 
//        file are UNIQUE AND EXCLUSIVELY in this file.

/**************************************************************************/

// Led pins
const int DATAPIN = 4;
const int CLOCKPIN = 5;

// Defintion of the pins
#define CAN0_INT 2

// Temperature-Voltage
const int TV_PIN=3;

// Carte Arrière Comm
const int H_PIN=12;   // Homing
const int N_PIN=6;   // Neutre

// Motoreducteur
const int MOTORED_FAIL_LED_PIN= A0;
const int STATE_FAIL_MOTORED_PIN= A2;

// Launch Control
const int LC_SWITCH_PIN = 7; // Pin à cahnger
const int LC_LED_PIN = A1;



#endif  /* inclusion guards - PROJECTCONFIG_H */ 
