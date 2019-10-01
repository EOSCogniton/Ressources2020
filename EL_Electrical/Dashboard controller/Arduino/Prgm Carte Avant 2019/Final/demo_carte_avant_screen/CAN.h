#ifndef CAN_H
#define CAN_H



/**************************************************************************/
//    Inclusion of the necessary libraries
/**************************************************************************/

#include <SPI.h>
#include <mcp_can.h>
#include "projectconfig.h"
#include "Gear_Update.h"
#include "Temp_Volt.h"



/**************************************************************************/
//    External variables and constants used by the functions in this file
/**************************************************************************/

extern MCP_CAN CAN0;

// R_ID=0x2000
extern signed Rpm;
extern signed TPS; // %
extern signed W_Temp;
extern signed A_Temp;

// R_ID=0x2001
extern signed Lambda; // x1000
extern signed Kph; // x10
extern signed O_Press;

// R_ID=0x2002
extern signed F_Press;
extern signed O_Temp;
extern signed Volts; // x10

// R_ID=0x2003
extern signed Gear;

// Temp Voltage (TV) display
extern int Switch_TV;



/**************************************************************************/
//    Functions
/**************************************************************************/

void Recieve();
/*
    @brief      Explication
    @param[in]  Parametres
    @return     Return
*/

void Data_Update(unsigned char Data[8]);
/*
    @brief      Explication
    @param[in]  Parametres
    @return     Return
*/

void Send_CA();
/*
    @brief      Explication
    @param[in]  Parametres
    @return     Return
*/



#endif
