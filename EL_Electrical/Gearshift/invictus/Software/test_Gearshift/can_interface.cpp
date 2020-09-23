/**************************************************************************/
/*!
    @file     can_interface.cpp
    @author   Arthur Rodriguez, Bruno Moreira Nabinger and Corentin Lepais
                                           (EPSA) Ecurie Piston Sport Auto
    
    The functions that initialize and manage the informations issued from 
    the CAN
 
    @section  HISTORY
    v1.0 - 19/02/2020 Changing the library to FlexCAN
    v0.3 - 06/12/2019 add function transmit
    V0.2 - 01/11/2018 
    v0.1 - 21/11/2018 First release ()
*/
/**************************************************************************/
#include "can_interface.h"

// Set CS to pin chipSelect (projectconfig.h) to object CAN0 (class MCP_CAN) 

FlexCAN CANbus(1000000);// Initialize the bus to 1000kb/s Link to the library https://github.com/teachop/FlexCAN_Library
//static CAN_message_t rmsg,tmsg; // Creates a struc of the r messages (received) et t messages (Transmitted)

unsigned long tmillis=millis();

/**************************************************************************/
/*!
    @brief   Initialize the bus to 1000kb/s
*/
/**************************************************************************/
can_interface::can_interface()
{   
    CANbus.begin();
    digitalWrite(LedPin,HIGH);
                    
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

void can_interface::Receive()
{
    //Implémenter les masques __ARS
    CANbus.read(rmsg);    
    Data_MAJ();
    }
    
    


/**************************************************************************/
/*!
    @brief  Interpretes the data from CAN
*/
/**************************************************************************/
void can_interface::Data_MAJ()
{   switch (rmsg.id) {
  
  case 0x1001:// Homing from front card
      Serial.println("id=0x1001, Front Card");
      
      homingState = rmsg.buf[0]*true;
      Serial.println("Homming : ");
      Serial.print(homingState);

      neutralState = rmsg.buf[1]*true;
      Serial.println("Neutral : ");
      Serial.print(neutralState);

      launchcontrolState = rmsg.buf[2]*true;
      Serial.println("Launch control : ");
      Serial.print(launchcontrolState);

      wetdryState = rmsg.buf[3]*true;
      Serial.println("wet Dry : ");
      Serial.print(wetdryState);

      tractionControlState = rmsg.buf[4]*true;
      Serial.println("Traction control : ");
      Serial.print(tractionControlState);
            
      logState = rmsg.buf[5]*true;
      Serial.println("Log DTA : ");
      Serial.print(logState);
          
    break;    

  case 0x2000:// RPM from DTA
    Serial.println("id=0x2000, RPM");
    RPM=rmsg.buf[0]+256*rmsg.buf[1];
    Serial.println(RPM);
    break;
    
  default:
    // statements
    break; 
}  
}

/**************************************************************************/
/*!
    @brief  Send the data to the CAN 
*/
/**************************************************************************/

void can_interface::Transmit(int gear, int error, boolean Auto)
{  
    tmsg.buf[0]=gear;
    tmsg.buf[1]=error;
    tmsg.buf[2]=Auto;
    for (int i = 3; i <= 7; i++) {
      tmsg.buf[i]=0;
    } 
    
    tmsg.id=0x1100;
    CANbus.write(tmsg);

}
