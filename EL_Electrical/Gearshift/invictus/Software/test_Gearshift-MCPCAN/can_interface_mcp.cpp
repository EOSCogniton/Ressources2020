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
    //Serial.print("\n");
    // Read data: Len = data length, Data = data byte(s)
    if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
    {
      //Serial.print("Reception, ID = ");
      CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);  
      // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
      if((R_ID_Mask & 0x80000000) == 0x80000000){
          //Serial.print("\n");
          //Serial.print("Extended, ID = ");
          R_ID=(R_ID_Mask & 0x0000FFFF);
          Data_MAJ();
          //Serial.println(R_ID);
      }
      else{
          //Serial.print("Standard, ID = ");
          //Serial.println(R_ID);
          //R_ID=0;
      }
        Data_MAJ();
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
    //Serial.print("\n");
    //Serial.println(R_ID);
    if(R_ID_Mask==0x100){ // Homing neutre launch wetdry traction log
        if (Data[0]==1){
            // Le bouton n'est pas appuyé (there is a pullup resistor on this button)
            homingState = false;
            //Serial.print("Homing :1,  ");       
        }else if (Data[0]==0){
            // le bouton est appuyé
            homingState = true;
            //Serial.print("Homing :0,  ");
        }

        if (Data[1]==1){
            // Le bouton n'est pas appuyé
            neutralState = false;
            //Serial.print("Neutral : 1,  ");
        }else if (Data[1]==0){
            // le bouton est appuyé
            neutralState = true;
            //Serial.print("Neutral : 0,  ");
        }
        if (Data[2]==1){
            // Le bouton n'est pas appuyé
            launchcontrolState = false;
            //Serial.print("LC:1,   ");
        }else if (Data[2]==0){
            // le bouton est appuyé
            launchcontrolState = true;
            //Serial.print("LC:0,   ");
        }
        if (Data[3]==1){
            // Le bouton n'est pas appuyé
            tractionControlState = false;
            //Serial.print("TC:1,  ");
        }else if (Data[3]==0){
            // le bouton est appuyé
            tractionControlState = true;
            //Serial.print("TC:0,  ");
        }
            
        if (Data[4]==1){
            // Le bouton n'est pas appuyé
            wetdryState = true;
            //Serial.print("Wet:1,   ");
        }else if (Data[4]==0){
            // le bouton est appuyé
            wetdryState = false;
            //Serial.print("Wet:0,  ");
        }

        if (Data[5]==1){
            // Le bouton n'est pas appuyé
            logState = false;
            //Serial.println("Log non");
        }else if (Data[5]==0){
            // le bouton est appuyé
            logState = true;
            //Serial.println("Log oui");
        }
        
    }
    if(R_ID==0x2000){ //RPM
        RPM=Data[0]+256*Data[1];
        //  Serial.print("RPM: ");
        //Serial.println(RPM);
    }
}

/**************************************************************************/
/*!
    @brief  Send the data to the CAN
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/

void can_interface::Transmit(int gear, boolean error, boolean Auto)
{  
    if (gear==-2)
      gear = 7;
    else if (gear==-1)
      gear = 8;

    char msgString[128];
    byte Data_msg[8]={gear, error, Auto, 0x00, 0x00, 0x00, 0x00, 0x00};
    /*for(byte i = 0; i<8; i++){
        sprintf(msgString, " 0x%.2X", Data_msg[i]);
        Serial.print(msgString);
      }
      Serial.println(" ");*/
    byte sndStat = CAN0.sendMsgBuf(0x110, 8, Data_msg); //0x1100
    if(sndStat == CAN_OK){
      //Serial.println("Message Sent Successfully!");
    } 
    else {
      Serial.println("Error Sending Message...");
    }
}
