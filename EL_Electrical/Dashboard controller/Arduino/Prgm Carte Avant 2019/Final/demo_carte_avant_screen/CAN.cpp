/***************************************************************************
  
   Function name: CAN
   
   Author:        Arthur Rodríguez (ARZ)
   
   Descriptions:  Exhaustive description of what all the functions in this 
                  file do and how they interact with each other.
                            
***************************************************************************/
#include "CAN.h"



/**************************************************************************/
//    Internal variables and constants used ONLY by the functions in this file
/**************************************************************************/

// Set CS to pin 10
MCP_CAN CAN0(10);

// 
long unsigned int R_ID_Mask;
long unsigned int R_ID;
unsigned char Len = 0;
unsigned char Data[8];
char Print[128];

// Carte Arrière Communication
int Switch_H;
int Switch_N;
byte Modif[8];
byte Null[8];

// Transmit var
unsigned long tmillis=millis();
unsigned long T_D_Millis=millis();
int T_Time=1000;



/**************************************************************************/
//    Functions
/**************************************************************************/

void Recieve(){
    Serial.print("\n");
    // Read data: Len = data length, Data = data byte(s)
    CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);      

    // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
    if((R_ID_Mask & 0x80000000) == 0x80000000){
        Serial.print("\n");
        Serial.print("Extended ");
        R_ID=(R_ID_Mask & 0x0000FFFF);
        Serial.print(R_ID);
        Data_Update(Data);
    }
    else{
        Serial.print("\n");
        Serial.print("Standart");
    }
}

void Data_Update(unsigned char Data[8]){  
    if(R_ID==0x2000){
        Rpm=Data[1]+256*Data[0];
        TPS=Data[3]+256*Data[2];
        W_Temp=Data[5]+256*Data[4];
        A_Temp=Data[7]+256*Data[6];
        
        sprintf(Print, "RPM = %5d   Throttle = %3d   Water Temp = %3d    Air Temp = %3d", Rpm, TPS, W_Temp, A_Temp);
        Serial.print("\n");
        Serial.print(Print);
        
        Seven_Seg_Calc(Switch_TV,W_Temp,Volts);
    }
    if(R_ID==0x2001){
        Lambda=Data[3]+256*Data[2];
        Kph=Data[5]+256*Data[4];
        O_Press=Data[7]+256*Data[6];
        
        sprintf(Print, "Lambda = %3d   KPH = %3d   Oil Press = %3d", Lambda, Kph, O_Press);
        Serial.print("\n");
        Serial.print(Print);
    }
    
    if(R_ID==0x2002){
        F_Press=Data[1]+256*Data[0];
        O_Temp=Data[3]+256*Data[2];
        Volts=Data[5]+256*Data[4];
        
        sprintf(Print, "Fuel Press = %3d   Oil Temp = %3d   Volts = %3d", F_Press, O_Temp, Volts);
        Serial.print("\n");
        Serial.print(Print);
        
        Seven_Seg_Calc(Switch_TV,W_Temp,Volts);
    }
    if(R_ID==0x1002){
        Gear=Data[0];
        
        sprintf(Print, "Gear = %1d", Gear);
        Serial.print("\n");
        Serial.print(Print);

        Gear_Update(Gear);
    }
    return;
}

void Send_CA(){
    Switch_H=digitalRead(H_PIN);
    Switch_N=digitalRead(N_PIN);

    sprintf(Print, "Switch_H = %1d   Switch_N = %1d", Switch_H, Switch_N);
    Serial.print("\n");
    Serial.print(Print);
    
    // Def des messages
    byte Modif[8]={0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    byte Null[8]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    tmillis=millis();
    if(tmillis>(T_D_Millis+T_Time)){ // Envoie discret de période T_Time
        T_D_Millis=millis();
        if(Switch_H==0){
            CAN0.sendMsgBuf(0x1000, 1, 8, Null);
        }
        if(Switch_H==1){
            CAN0.sendMsgBuf(0x1000, 1, 8, Modif);
        }
        if(Switch_N==0){
            CAN0.sendMsgBuf(0x1001, 1, 8, Null);
        }
        if(Switch_N==1){
            CAN0.sendMsgBuf(0x1001, 1, 8, Modif);
        }
    }
}



/***************************************************************************
  END FILE
***************************************************************************/
