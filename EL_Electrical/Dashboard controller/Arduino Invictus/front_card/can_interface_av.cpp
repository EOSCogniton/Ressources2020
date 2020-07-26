/**************************************************************************/
/*!
    @file     can_interface.cpp
    @author   Arthur Rodriguez, Bruno Moreira Nabinger and Corentin Lepais
                                           (EPSA) Ecurie Piston Sport Auto
    
    The functions that initialize and manage the informations issued from 
    the CAN
 
    @section  HISTORY
    v1.0 - 25/07/2020 creation
*/
/**************************************************************************/
#include "can_interface_av.h"

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
    //digitalWrite(LedPin,HIGH);

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
{   
  switch (rmsg.id) {
     case 0x2000:// RPM from DTA, water temp
      Serial.println("id=0x2000, RPM, Température eau, TPS(%)");
      RPM=rmsg.buf[0]+256*rmsg.buf[1];
      waterTemp=rmsg.buf[4]+256*rmsg.buf[5];
      throttle=rmsg.buf[2]+256*rmsg.buf[3];
      Serial.print(RPM);
      Serial.print(", ");
      Serial.print(waterTemp);
      Serial.print(", ");
      Serial.println(throttle);
      break;
      
    case 0x2001:// Pression air, lambda, KPH, pression huile
      Serial.println("id=0x2000,Pression plenum (kPa), lambda, KPH, pression huile (kPa)");
      plenum=rmsg.buf[0]+256*rmsg.buf[1];
      Lambda=(rmsg.buf[2]+256*rmsg.buf[3])/1000;
      Kph=(rmsg.buf[4]+256*rmsg.buf[5])/10;
      oilPressure=rmsg.buf[6]+256*rmsg.buf[7];
      Serial.print(Lambda);
      Serial.print(", ");
      Serial.print(Kph);
      Serial.print(", ");
      Serial.println(oilPressure);
      break;
      
    case 0x2002:// Pression essence, Volt, conso essence L/h
      Serial.println("id=0x2002, tension batterie  air, conso essence L/h");
      Volts=(rmsg.buf[4]+256*rmsg.buf[5])/10;
      FuelConHR=(rmsg.buf[6]+256*rmsg.buf[7])/10;
      Serial.print(Volts);
      Serial.print(" V, ");
      Serial.println(FuelConHR);
      break;  

    case 0x2003:// Gear, advance deg, injection, conso essence L/100km
      Serial.println("id=0x2003,  advance deg, injection, conso essence L/100km");
      AdvanceDeg=(rmsg.buf[2]+256*rmsg.buf[3])/10;
      FuelConKM=(rmsg.buf[6]+256*rmsg.buf[7])/10;
      Inject=(rmsg.buf[4]+256*rmsg.buf[5])/100;
      Serial.print(AdvanceDeg);
      Serial.print(" V, ");
      Serial.print(Inject);
      Serial.print(" ms, ");
      Serial.println(FuelConKM);
      break;      
 
    case 0x2004:// CamAdvance
      Serial.println("id=0x2004, Cam avance");
      CamAdv=(rmsg.buf[6]+256*rmsg.buf[7])/10;
      CamTarg=0;
      CamPWM=0;
      Serial.println(CamAdv);
      break; 
    case 0x2005:// CamAdvance
      Serial.println("id=0x2004, Cam Targ, Cam PWM");
      CamTarg=(rmsg.buf[0]+256*rmsg.buf[1])/10;
      CamPWM=(rmsg.buf[2]+256*rmsg.buf[3])/10;
      Serial.print(CamTarg);
      Serial.print(", ");
      Serial.print(CamPWM);
      break;   
            
    case 0x1100: //Rear Card
      Serial.println("id=0x1100, Rear Card");
      gear=rmsg.buf[0];
      Serial.println("Vitesse : ");
      Serial.print(gear);
  
      errorMotored=rmsg.buf[1];
      Serial.println("Errreur motoréducteur : ");
      Serial.print(errorMotored);

      auto_mode=rmsg.buf[2]*true;
      Serial.println("Mode auto : ");
      Serial.print(auto_mode);
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

void can_interface::Transmit(boolean homing, boolean neutre, boolean logDta, boolean TCState, boolean LCState, boolean WDState)
{  
    tmsg.buf[0]=homing;
    tmsg.buf[1]=neutre;
    tmsg.buf[2]=logDta;
    tmsg.buf[3]=TCState;
    tmsg.buf[4]=LCState;
    tmsg.buf[5]=WDState;
    tmsg.buf[6]=0;
    tmsg.buf[7]=0;
    tmsg.id=0x1100;
    CANbus.write(tmsg);

}
