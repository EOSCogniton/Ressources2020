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
#include "Adafruit_MCP23008.h"
#include <Adafruit_DotStar.h>

#include "CAN.h"
#include "Gear_Update.h"
#include "Led_Strip.h"
#include "Temp_Volt.h"
#include "projectconfig.h"
#include "State_LC.h"

Adafruit_MCP23008 mcp;


/**************************************************************************/
//    Variables used by various functions in various .h files
/**************************************************************************/

//  Data variables
//    R_ID=0x2000
signed Rpm;
bool Data_Rpm;
signed TPS; // %
signed W_Temp;
signed W_Temp_B;
signed A_Temp;

//    R_ID=0x2001
signed Lambda; // x1000
signed Kph; // x10
signed O_Press=2;

//    R_ID=0x2002
signed F_Press;
signed O_Temp;
signed Volts; // x10
signed Volts_B; // x10

//    R_ID=0x1002
signed Gear=0;
signed Error;
signed Auto;

//    R_ID=0x2007
signed ECU;
signed Led_LC;

//  Gear display
int Init_Seven_Segments;

//  Temp Voltage (TV) display
int Switch_TV;
int Switch_TV_B;

// Led Strip Display
int Count=0;

/**************************************************************************/
//    Setup and loop
/**************************************************************************/

void setup(){

   
  
    // PIN Setup
    pinMode(TV_PIN,INPUT_PULLUP);

    pinMode(H_PIN,INPUT_PULLUP);
    pinMode(N_PIN,INPUT_PULLUP);

    pinMode(LC_LED_PIN,OUTPUT);
    pinMode(MOTORED_FAIL_LED_PIN,OUTPUT);

    
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

    
    // Turn Off all Seven Segment
    for(Init_Seven_Segments=0;Init_Seven_Segments<=2;Init_Seven_Segments++){ //This shuts off all segments at the begining
        mcp.begin(Init_Seven_Segments);
        for(int i=0;i<=7;i++){
            mcp.pinMode(i,OUTPUT);
            mcp.digitalWrite(i,1);
        }
        Serial.println("7 Segment Init Successfully!");
    }
    if(!digitalRead(CAN0_INT)){ 
      Send_CA();
    }
    Led_Init();
     // Gear Init
    Gear_Init();

}


void loop(){
    // Read the Switch position
    Switch_TV=digitalRead(TV_PIN);
//    Serial.println("\n");
//    Serial.println("TV :" );
//    Serial.println(Switch_TV);
    // Variables are updated
    // If CAN0_INT pin is low, read receive buffer
    if(!digitalRead(CAN0_INT)){   

        // Variables are received and processed
        Recieve();

        // Led Strip Maj
        if(Data_Rpm==1){
//            Serial.println("\n");
//            Serial.println("RPM : ");
//            Serial.println(abs(Rpm));
            Engine_Failure(W_Temp,A_Temp,O_Press);
            Tachometer(abs(Rpm),1,Auto);
        }
        if (Switch_TV != Switch_TV_B || W_Temp != W_Temp_B || Volts != Volts_B){
          Seven_Seg_Calc(Switch_TV,W_Temp,Volts);
          Switch_TV_B = Switch_TV;
          W_Temp_B = W_Temp;
          Volts_B = Volts;
        }
        Send_CA();
    }
}
