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
     FuelPressure=0;
     Lambda=0;
     Kph=0;
     Volts=0;
     FuelConHR=0;
     AdvanceDeg=0;
     Inject=0;
     FuelConKM=0;
     CamAdv=0;
     CamTarg=0;
     CamPWM=0;
     waterTemp=0;
     gear=0;
     errorMotored=0;     
     auto_mode=false;
     RPM=0;  
     throttle=0;
     oilPressure=0;
     plenum=0;
}

/**************************************************************************/
/*!
    @brief   Accesseur: Send the state of each attribut
*/
/**************************************************************************/

void can_interface::Recieve()
{
    if(!digitalRead(CAN0_INT))  
      {
      //Serial.print("Réception: ");
      // Read data: Len = data length, Data = data byte(s)
      CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);      
  
      // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
      if((R_ID_Mask & 0x80000000) == 0x80000000){ 
          R_ID=(R_ID_Mask & 0x0000FFFF);
          //Serial.print("Extended, ID = ");  
          //Serial.println(R_ID);
      }
      else{
          //Serial.println("Standard");
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
  if(R_ID==0x2000){
    //Serial.println("id=0x2000, RPM, Température eau, TPS(%)");
    RPM=Data[0]+256*Data[1];
    waterTemp=Data[4]+256*Data[5];
    throttle=Data[2]+256*Data[3];
    /*Serial.print(RPM);
    Serial.print(", ");
    Serial.print(waterTemp);
    Serial.print(", ");
    Serial.println(throttle);*/
  }

  if(R_ID==0x2001){ 
      //Serial.println("id=0x2000,Pression plenum (kPa), lambda, KPH, pression huile (kPa)");
      plenum=Data[0]+256*Data[1];
      Lambda=(Data[2]+256*Data[3]);
      Kph=(Data[4]+256*Data[5])/10;
      oilPressure=Data[6]+256*Data[7];
      /*Serial.print(Lambda);
      Serial.print(", ");
      Serial.print(Kph);
      Serial.print(", ");
      Serial.println(oilPressure);*/
  }
    if(R_ID==0x2002){ 
      //Serial.println("id=0x2002, fuel pressure, tension batterie, conso essence L/h");
      FuelPressure = Data[0]+256*Data[1];
      //Serial.print(FuelPressure);
      //Serial.print(',');
      Volts=(Data[4]+256*Data[5]);
      //FuelConHR=(Data[6]+256*Data[7])/10;
      //Serial.print(Volts);
      //Serial.println(" V, ");
      //Serial.println(FuelConHR);
  }
  /*if(R_ID==0x2003){ 
      Serial.println("id=0x2003,  advance deg, injection, conso essence L/100km");
      AdvanceDeg=(Data[2]+256*Data[3])/10;
      FuelConKM=(Data[6]+256*Data[7])/10;
      Inject=(Data[4]+256*Data[5])/100;
      Serial.print(AdvanceDeg);
      Serial.print(" V, ");
      Serial.print(Inject);
      Serial.print(" ms, ");
      Serial.println(FuelConKM);
  }
   if(R_ID==0x2004){ 
      Serial.println("id=0x2004, Cam avance");
      CamAdv=(Data[6]+256*Data[7])/10;
      CamTarg=0;
      CamPWM=0;
      Serial.println(CamAdv);
  }
  if(R_ID==0x2005){ 
      Serial.println("id=0x2004, Cam Targ, Cam PWM");
      CamTarg=(Data[0]+256*Data[1])/10;
      CamPWM=(Data[2]+256*Data[3])/10;
      Serial.print(CamTarg);
      Serial.print(", ");
      Serial.print(CamPWM);
  }*/

  if(R_ID==0x2007){
    LC_state=bitRead(Data[6], 6); //read just one bit of the data
    Serial.print("id=0x2007, LC state : ");
    Serial.println(LC_state);
  }

  
  if(R_ID_Mask==0x110){ 
      //Serial.println("id=0x110, Rear Card");
      gear=Data[0];
      //Serial.print("Vitesse : ");
      //Serial.println(gear);
  
      errorMotored=Data[1];
      //Serial.print("Errreur motoréducteur : ");
      //Serial.println(errorMotored);

      auto_mode=Data[2]*true;
      //Serial.print("Mode auto : ");
      //Serial.println(auto_mode);
  }
  
  
}

/**************************************************************************/
/*!
    @brief  Send the data to the CAN
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/

void can_interface::Transmit(boolean homing, boolean neutre, boolean logDta, boolean TCState, boolean LCState, boolean WDState)
{  
    
    byte Data_msg[8]={homing, neutre, LCState, TCState, WDState, logDta, 0x00, 0x00};
    /*char msgString[128];
    for(byte i = 0; i<8; i++){
        sprintf(msgString, " 0x%.2X", Data_msg[i]);
        Serial.print(msgString);
      }
      Serial.println(" ");*/
    byte sndStat = CAN0.sendMsgBuf(0x100, 8, Data_msg); //0x1001
    if(sndStat == CAN_OK){
      //Serial.println("Message Sent Successfully!");
    } 
    else {
      Serial.println("Error Sending Message...");
    }
}
