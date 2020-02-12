/**************************************************************************/
/*!
    @file     can_interface.h
    @author   Arthur Rodriguez, Bruno Moreira Nabinger and Corentin Lepais
                                           (EPSA) Ecurie Piston Sport Auto
    
    Contain the prototypes of the functions that initialize and  manage the 
    information issued from the CAN. They are defined in the file 
    can_interface.cpp

 
    @section  HISTORY
    v0.3 - 13/02/2019 Transmit, and attributs added
    V0.2 - 01/11/2018 
    v0.1 - 21/11/2018 First release ()
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
    boolean neutreState;
    int RPM;
    long unsigned int R_ID_Mask;
    

    boolean shiftcutState;
    boolean gearpotState;
    boolean lunchcontrolState;
    boolean wetdryState;     
   
    

private:
    void Data_MAJ();
public:
    can_interface();
    void Receive();
    void Transmit(int gear, int error, boolean Auto);
    boolean getHomingState();
    boolean getNeutreState();
    int getRPM();
    boolean getShiftcutState();
    boolean getGearpotState();
    boolean getLunchcontrolState();
    boolean getWetdryState();
};






#endif /* inclusion guards - CAN_INTERFACE_H */
