/**************************************************************************/
/*
    @file     main_carte_avant
    
    @authors  Arthur Rodríguez (ARZ)
              Martín Gómez-Valcárcel (MGV)
                for   Ecurie Piston Sport Auto (EPSA)
                at    École Centrale de Lyon (ECL)
    
    @functions and files
        CAN.h
            Recieve : Receipt of all information by CAN
            Data_Update : Updates information
            Send_CA : Send of all information by CAN
        Gear_Update.h
            Gear_Update : Updates the gear shown in the seven segments
        Led_Strip.h
            Engine_Failure : Flashes in red the LED strip
            Tachometer : Calculates the number of LEDs to illuminate
            Led_Update : Updates the LED strip
        State_LC.h
            State_LC
        Temp_Volt.h
            Seven_Seg_Calc : Calculates the segments to iluminate of the
                             seven segments
            TV_Update : Updates the seven segments showing temperature or
                        voltage
        projectconfig.h : Storage of all PINS configurations of the Arduino
    
    @history  v0.1 - 06/02/2019 First release

*/
/**************************************************************************/



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/

#include <SPI.h>
#include <mcp_can.h>
#include <Adafruit_DotStar.h>

#include "CAN.h"
#include "Screen128x64.h"
#include "Led_Strip.h"
#include "Temp_Volt.h"
#include "projectconfig.h"
#include "State_LC.h"


/**************************************************************************/
//    Variables used by various functions in various .h files
/**************************************************************************/

//  Data variables
//    R_ID=0x2000
signed Rpm;
signed TPS; // %
signed W_Temp;
signed A_Temp;

//    R_ID=0x2001
signed Lambda; // x1000
signed Kph; // x10
signed O_Press=2;

//    R_ID=0x2002
signed F_Press;
signed O_Temp;
signed Volts; // x10

//    R_ID=0x2003
signed Gear;

//  Gear display
int Init_Seven_Segments;

//  Temp Voltage (TV) display
int Switch_TV;

/**************************************************************************/
//    Setup and loop
/**************************************************************************/

void setup(){
  
    // PIN Settup
    pinMode(TV_PIN,INPUT);

    pinMode(H_PIN,INPUT);
    pinMode(N_PIN,INPUT);

    pinMode(LC_SWITCH_PIN,INPUT); 
    pinMode(LC_LED_PIN,OUTPUT);

    // Motored
    pinMode(MOTORED_FAIL_LED_PIN,OUTPUT);
    pinMode(STATE_FAIL_MOTORED_PIN,OUTPUT);

    digitalWrite(MOTORED_FAIL_LED_PIN,LOW);
    digitalWrite(STATE_FAIL_MOTORED_PIN,LOW);

    
    // CAN Init
    Serial.begin(115200);
    // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled
    if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK){
        Serial.println("CAN Init Successfully!");}
    else{
        Serial.println("CAN Init Failure");}
    // Set operation mode to normal so the MCP2515 sends acks to received data
    CAN0.setMode(MCP_NORMAL);                  
    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT); 


    Led_Init();

    // Gear Init
    
    // Gear_Init();

    Screen_Init();

}


void loop(){
    // Code de demo

    for(Gear=1;Gear<=4;Gear++){
        for(Rpm=0;Rpm<=10;Rpm++){
            Screen_Update(Gear,91+Rpm,104-Rpm);
            //Gear_Update(Gear);
            Tachometer((Rpm*50+9000),Gear);
            delay(40);
        }
    }
}
