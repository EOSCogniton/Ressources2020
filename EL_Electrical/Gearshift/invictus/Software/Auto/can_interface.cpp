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

FlexCAN CANbus(1000000);// Initialize the bus to 1000kb/s
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
    digitalWrite(13,HIGH);
                    
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

boolean can_interface::getShiftcutState()
{
  return shiftcutState;
}

boolean can_interface::getGearpotState()
{
  return gearpotState;
}

boolean can_interface::getLunchcontrolState()
{
  return lunchcontrolState;
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
    @param[in] unsigned char Data[8] 
*/
/**************************************************************************/
void can_interface::Data_MAJ()
{   
    if(rmsg.id==0x1001){ // Homing
        if (rmsg.buf[0]==17){
            // Le bouton n'est pas appuyé (there is a pullup resistor on this button)
            homingState = false;
            //Serial.print("0");       
        }
        if (rmsg.buf[0]==0){
            // le bouton est appuyé
            homingState = true;
            //Serial.print("1");
        }
    }
    if(rmsg.id==0x1002){ // Neutre
        if (rmsg.buf[0]==17){
            // Le bouton n'est pas appuyé
            neutreState = false;
            //Serial.print("0");
        }
        if (rmsg.buf[0]==0){
            // le bouton est appuyé
            neutreState = true;
            //Serial.print("1");
        }
    }
    if(rmsg.id==0x2000){ //RPM
        RPM=rmsg.buf[0]+256*rmsg.buf[1];
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
  
  
    tmsg.buf=[gear, error, Auto, 0x00, 0x00, 0x00, 0x00, 0x00];
    tmsg.id=0x1100;
    tmillis=millis();
    if(tmillis>(T_D_millis+T_Time)){ // Envoie discret de période T_Time
        
        T_D_millis=millis();
        CANbus.write(tmsg);
        
    }
}
