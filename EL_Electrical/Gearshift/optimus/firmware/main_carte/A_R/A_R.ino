// CAN_Rec_4

#include <SPI.h>
#include <mcp_can.h>

// Defintion of the pins
// Set INT to pin 2
#define CAN0_INT 2 
// Set CS to pin 10
MCP_CAN CAN0(10); 
const int DATAPIN = 1;
const int CLOCKPIN = 3;


// Recieve variables init
long unsigned int R_ID_Mask;
long unsigned int R_ID;
unsigned char Len = 0;
unsigned char Data[8];
char Print[128];  



void setup(){
    Serial.begin(115200);
  
    // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled
    if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK){
        Serial.println("Init Successfully!");
    }
    else{
        Serial.println("Init Failure");
    }

    // Set operation mode to normal so the MCP2515 sends acks to received data
    CAN0.setMode(MCP_NORMAL);                  

    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT);                            
}

void Data_MAJ(unsigned char Data[8]){  
    Serial.print("\n");
    if(R_ID==0x1000){ // Reset Motored
        if (Data[0]==0){
            // Le bouton est appuyé
            Serial.print("0");
        }
        if (Data[0]==17){
            // le bouton n'est pas appuyé
            Serial.print("1");
        }
    }
    if(R_ID==0x1001){ // Homing
        if (Data[0]==0){
            // Le bouton est appuyé
            Serial.print("0");
        }
        if (Data[0]==17){
            // le bouton n'est pas appuyé
            Serial.print("1");
        }
    }
    if(R_ID==0x1002){ // Neutre
        if (Data[0]==0){
            // Le bouton est appuyé
            Serial.print("0");
        }
        if (Data[0]==17){
            // le bouton n'est pas appuyé
            Serial.print("1");
        }
    }
}

void Recieve(){
    Serial.print("\n");
    // Read data: Len = data length, Data = data byte(s)
    CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);      

    // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
    if((R_ID_Mask & 0x80000000) == 0x80000000){
        Serial.print("\n");
        Serial.print("Extended");
        R_ID=(R_ID_Mask & 0x0000FFFF);
        Data_MAJ(Data);
    }
    else{
        Serial.print("\n");
        Serial.print("Standart");
    }
}

void loop(){
    
    // On met les variables à jour
    // If CAN0_INT pin is low, read receive buffer
    if(!digitalRead(CAN0_INT)){   

        // On recoit et on traite les données
        Recieve();
    }
}
