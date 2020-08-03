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
    Serial.print("Réception: ");
    // Read data: Len = data length, Data = data byte(s)
    CAN0.readMsgBuf(&R_ID_Mask, &Len, Data);      

    // Determine if R_ID_Mask is standard (11 bits) or extended (29 bits)
    if((R_ID_Mask & 0x80000000) == 0x80000000){
        Serial.println("Extended");
        R_ID=(R_ID_Mask & 0x0000FFFF);
        Data_MAJ();
    }
    else{
        Serial.println("Standard");
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
    Serial.println("id=0x2000, RPM, Température eau, TPS(%)");
    RPM=Data[0]+256*Data[1];
    waterTemp=Data[4]+256*Data[5];
    throttle=Data[2]+256*Data[3];
    Serial.print(RPM);
    Serial.print(", ");
    Serial.print(waterTemp);
    Serial.print(", ");
    Serial.println(throttle);
  }

  if(R_ID==0x2001){ 
      Serial.println("id=0x2000,Pression plenum (kPa), lambda, KPH, pression huile (kPa)");
      plenum=Data[0]+256*Data[1];
      Lambda=(Data[2]+256*Data[3])/1000;
      Kph=(Data[4]+256*Data[5])/10;
      oilPressure=Data[6]+256*Data[7];
      Serial.print(Lambda);
      Serial.print(", ");
      Serial.print(Kph);
      Serial.print(", ");
      Serial.println(oilPressure);
  }
    if(R_ID==0x2002){ 
      Serial.println("id=0x2002, tension batterie  air, conso essence L/h");
      Volts=(Data[4]+256*Data[5])/10;
      FuelConHR=(Data[6]+256*Data[7])/10;
      Serial.print(Volts);
      Serial.print(" V, ");
      Serial.println(FuelConHR);
  }
  if(R_ID==0x2003){ 
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
  }
  if(R_ID==0x1100){ 
      Serial.println("id=0x1100, Rear Card");
      gear=Data[0];
      Serial.println("Vitesse : ");
      Serial.print(gear);
  
      errorMotored=Data[1];
      Serial.println("Errreur motoréducteur : ");
      Serial.print(errorMotored);

      auto_mode=Data[2]*true;
      Serial.println("Mode auto : ");
      Serial.print(auto_mode);
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
    byte Data_msg[8]={homing, neutre, logDta, TCState, LCState, WDState, 0x00, 0x00};
    CAN0.sendMsgBuf(0x1002, 1, 8, Data_msg);
}
