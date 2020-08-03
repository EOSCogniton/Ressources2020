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
#include "can_interface_mcp.h"

// Set CS to pin chipSelect (projectconfig.h) to object CAN0 (class MCP_CAN) 
MCP_CAN CAN0(10); 

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
        Serial.println("Init Successfully!");
        digitalWrite(13,HIGH);
    }
    else{
        Serial.println("Init Failure");
    }

    // Set operation mode to normal so the MCP2515 sends acks to received data
    CAN0.setMode(MCP_NORMAL);                  

    // Configuring pin for /INT input
    pinMode(CAN0_INT, INPUT);   

   // Initialisation of each attribut
   homingState = false;
   neutralState = false;
   tractionControlState = false;
   logState = false;
   wetdryState = false;
   launchcontrolState = false;
   wetdryState = false;
   RPM = 0;
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

boolean can_interface::getNeutralState()
{
  return neutralState;
}

int can_interface::getRPM()
{
  return RPM;
}

boolean can_interface::getTractionState()
{
  return tractionControlState;
}

boolean can_interface::getLogState()
{
  return logState;
}

boolean can_interface::getLaunchcontrolState()
{
  return launchcontrolState;
}

boolean can_interface::getWetdryState()
{
  return wetdryState;
}

void can_interface::Recieve()
{
    Serial.print("\n");
    // Read data: Len = data length, Data = data byte(s)
    CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);      

    // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
    if((R_ID_Mask & 0x80000000) == 0x80000000){
        Serial.print("\n");
        Serial.print("Extended");
        R_ID=(R_ID_Mask & 0x0000FFFF);
        Data_MAJ();
    }
    else{
        Serial.print("\n");
        Serial.print("Standard");
    }
}

/**************************************************************************/
/*!
    @brief  Interpretes the data from CAN
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/
void can_interface::Data_MAJ()
{   
    Serial.print("\n");
    if(R_ID==0x1001){ // Homing neutre launch wetdry traction log
        if (Data[0]==17){
            // Le bouton n'est pas appuyé (there is a pullup resistor on this button)
            homingState = false;
            Serial.println("Homing non");       
        }else if (Data[0]==0){
            // le bouton est appuyé
            homingState = true;
            Serial.println("Homing oui");
        }

        if (Data[1]==17){
            // Le bouton n'est pas appuyé
            neutralState = false;
            Serial.println("neutre non");
        }else if (Data[1]==0){
            // le bouton est appuyé
            neutralState = true;
            Serial.println("neutre oui");
        }
        if (Data[2]==17){
            // Le bouton n'est pas appuyé
            launchcontrolState = false;
            Serial.println("LC non");
        }else if (Data[2]==0){
            // le bouton est appuyé
            launchcontrolState = true;
            Serial.println("LC oui");
        }
        if (Data[3]==17){
            // Le bouton n'est pas appuyé
            wetdryState = false;
            Serial.println("Wet non");
        }else if (Data[3]==0){
            // le bouton est appuyé
            wetdryState = true;
            Serial.println("Wet oui");
        }
        if (Data[4]==17){
            // Le bouton n'est pas appuyé
            tractionControlState = false;
            Serial.println("TC non");
        }else if (Data[4]==0){
            // le bouton est appuyé
            tractionControlState = true;
            Serial.println("TC oui");
        }
        if (Data[5]==17){
            // Le bouton n'est pas appuyé
            logState = false;
            Serial.println("Log non");
        }else if (Data[5]==0){
            // le bouton est appuyé
            logState = true;
            Serial.println("Log oui");
        }
        
    }
    if(R_ID==0x2000){ //RPM
        RPM=Data[0]+256*Data[1];
        Serial.print("RPM: ");
        Serial.println(RPM);
    }
}

/**************************************************************************/
/*!
    @brief  Send the data to the CAN
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/

void can_interface::Transmit(int gear, int error, boolean Auto)
{  
    byte Data_msg[8]={gear, error, Auto, 0x00, 0x00, 0x00, 0x00, 0x00};
    CAN0.sendMsgBuf(0x1002, 1, 8, Data_msg);
}
