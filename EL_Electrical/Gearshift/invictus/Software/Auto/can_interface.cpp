/**************************************************************************/
/*!
    @file     can_interface.cpp
    @author   Arthur Rodriguez, Bruno Moreira Nabinger and Corentin Lepais
                                           (EPSA) Ecurie Piston Sport Auto
    
    The functions that initialize and manage the informations issued from 
    the CAN
 
    @section  HISTORY
    v0.3 - 06/12/2019 add function transmit
    V0.2 - 01/11/2018 
    v0.1 - 21/11/2018 First release ()
*/
/**************************************************************************/
#include "can_interface.h"

// Set CS to pin chipSelect (projectconfig.h) to object CAN0 (class MCP_CAN) 
MCP_CAN CAN0(chipSelect); 

unsigned long tmillis=millis();

/**************************************************************************/
/*!
    @brief   Initialize MCP2515 running at 16MHz with a baudrate of 
               1000kb/s and the masks and filters disabled
             Set operation mode to normal so the MCP2515 sends acks to
                received data
             Configuring pin intPinCAN for /INT input
*/
/**************************************************************************/
can_interface::can_interface()
{   
    Len = 0;
  
    // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled
    if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK){
        //Serial.println("Init Successfully!");
        digitalWrite(13,HIGH);
    }
    else{
        //Serial.println("Init Failure");
    }

    // Set operation mode to normal so the MCP2515 sends acks to received data
    CAN0.setMode(MCP_NORMAL);                  

    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT);   

   // Initialisation of each attribut
   homingState = true;
   neutreState = true;
}

/**************************************************************************/
/*!
    @brief   Accesseur: Send the state of each attribut
*/
/**************************************************************************/

boolean can_interface::getHomingState()
{
  return homingState;
}

boolean can_interface::getNeutreState()
{
  return neutreState;
}

int can_interface::getRPM()
{
  return RPM;
}

void can_interface::Recieve()
{
    //Serial.print("\n");
    // Read data: Len = data length, Data = data byte(s)
    CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);      

    // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
    if((R_ID_Mask & 0x80000000) == 0x80000000){
        //Serial.print("\n");
        //Serial.print("Extended");
        R_ID=(R_ID_Mask & 0x0000FFFF);
        Data_MAJ();
    }
    else{
        //Serial.print("\n");
        //Serial.print("Standart");
    }
}

/**************************************************************************/
/*!
    @brief  Interpretes the data from CAN
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/
void can_interface::Data_MAJ()
{   //Serial.print("\n");
    if(R_ID==0x1000){ // Homing
        if (Data[0]==17){
            // Le bouton n'est pas appuyé (there is a pullup resistor on this button)
            homingState = false;
            //Serial.print("0");       
        }
        if (Data[0]==0){
            // le bouton est appuyé
            homingState = true;
            //Serial.print("1");
        }
    }
    if(R_ID==0x1001){ // Neutre
        if (Data[0]==17){
            // Le bouton n'est pas appuyé
            neutreState = false;
            //Serial.print("0");
        }
        if (Data[0]==0){
            // le bouton est appuyé
            neutreState = true;
            //Serial.print("1");
        }
    }
    if(R_ID==0x2000){ //RPM
        RPM=Data[0]+256*Data[1];
    }
}

/**************************************************************************/
/*!
    @brief  Send the data to the CAN
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/

unsigned long T_D_millis=millis();
unsigned long T_Time=100;

void can_interface::Transmit(int gear, int error, boolean Auto)
{  
    byte Data_msg[8]={gear, error, Auto, 0x00, 0x00, 0x00, 0x00, 0x00};
    tmillis=millis();
    if(tmillis>(T_D_millis+T_Time)){ // Envoie discret de période T_Time
        T_D_millis=millis();
        CAN0.sendMsgBuf(0x1002, 1, 8, Data_msg);
    }
}
