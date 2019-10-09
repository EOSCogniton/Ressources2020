#ifndef Nextion
#define Nextion

// Libraries
#include "Arduino.h"

// Variables

extern String Gear;
extern int Speed;

// Functions

void Nextion_Init();

void MAJ_Page(int Page);

void MAJ_Gear(String Gear);

void MAJ_Speed(String Speed);

void MAJ_RPM(String RPM);

void MAJ_RPM_Bar(String RPM_Bar);

void MAJ_Bat(String Bat);

void MAJ_E_Temp(String E_Temp);

void MAJ_Fuel(String Fuel);

void MAJ_T_Temp(String T_Temp);

void MAJ_Lap(String Lap);

void MAJ_D_Prev(String Delta);

void MAJ_D_Suiv(String Delta);

void MAJ_Best_Lap(String B_Lap);

void MAJ_Last_Lap(String B_Lap);

void MAJ_Delta_Lap(String D_Lap);

void MAJ_Current_Lap(String B_Lap);

void MAJ_Pedal(String Pedal);

String MAJ_Color(String Color);

void End();

#endif
