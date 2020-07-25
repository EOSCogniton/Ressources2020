/**************************************************************************/
/*!
    @file     can_interface.h
    @author   Arthur Rodriguez, Bruno Moreira Nabinger and Corentin Lepais
                                           (EPSA) Ecurie Piston Sport Auto
    
    Contain the prototypes of the functions that initialize and  manage the 
    information issued from the CAN. They are defined in the file 
    can_interface.cpp

 
    @section  HISTORY
    v0.1 - 25/07/2020 redaction
*/
/**************************************************************************/

//Protection against multiple inclusions
#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include "FlexCAN.h"

#include "projectconfig.h" 

// Defintion of the pins
// Set INT to pin intPinCAN (projectconfig.h)
#define CAN0_INT intPinCAN 
// Set CS to pin chipSelect (projectconfig.h) to object CAN0 (class MCP_CAN) 
extern FlexCAN CANbus; 

class can_interface
{
    private: //Trouver un moyen de rajouter tmsg et rmsg __ARS
      struct CAN_message_t tmsg;
      struct CAN_message_t rmsg;
      boolean homingState;
      boolean neutralState;
      long unsigned int R_ID_Mask;


      boolean logState;
      boolean tractionControlState;
      boolean launchcontrolState;
      boolean wetdryState;    
      boolean logRaceCapture;
      
  public:
        float Lambda;
        float Kph;
        float Volts;
        float FuelConHR;
        float AdvanceDeg;
        float Inject;
        float FuelConKM;
        float CamAdv;
        float CamTarg;
        float CamPWM;
        float waterTemp;
        int gear;
        int errorMotored;
        bool auto_mode;
        int RPM;
  
  private:
      void Data_MAJ();
  public:
      can_interface();
      void Receive();
      void Transmit(boolean homing, boolean neutre, boolean logDta, boolean TCState, boolean LCState, boolean WDState, boolean logRaceCap);
      void setHomingState(boolean etat);
      void setNeutralState(boolean etat);
      void setTractionState(boolean etat);
      void setLogState(boolean etat);
      void setLaunchcontrolState(boolean etat);
      void setWetdryState(boolean etat);
      void setlogRaceCapture(boolean etat);
};






#endif /* inclusion guards - CAN_INTERFACE_H */
