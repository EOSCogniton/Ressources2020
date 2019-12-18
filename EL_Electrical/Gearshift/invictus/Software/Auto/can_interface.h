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

#include <SPI.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include "projectconfig.h" 

// Defintion of the pins
// Set INT to pin intPinCAN (projectconfig.h)
#define CAN0_INT intPinCAN 
// Set CS to pin chipSelect (projectconfig.h) to object CAN0 (class MCP_CAN) 
extern MCP_CAN CAN0; 

class can_interface
{
    private:
    //MCP_CAN CAN0(10); 
    boolean homingState;
    boolean neutreState;
    int RPM;
    long unsigned int R_ID_Mask;
    long unsigned int R_ID;
    unsigned char Data[8];
    // Recieve variables init
    unsigned char Len; 

private:
    void Data_MAJ();
public:
    can_interface();
    void Recieve();
    void Transmit(int gear, int error, boolean Auto);
    boolean getHomingState();
    boolean getNeutreState();
    int getRPM();
};






#endif /* inclusion guards - CAN_INTERFACE_H */
