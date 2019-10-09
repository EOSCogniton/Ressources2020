// Libraries
#include "Comm_PC.h"
#include "LedStrip.h"
#include "Nextion.h"

// Variables

int Page=0;
String Msg;
String ID;
String Data;

// Functions

void MAJ_Data(){
    if(Serial.available()){
        
        if(Page==0){
            MAJ_Page(2);
            Page=2;
        }
        
        Msg=Serial.readStringUntil('\x0!');
        ID=Msg.substring(0,2);
        Data=Msg.substring(3);
    
        if (ID=="01"){
            MAJ_Gear(Data);
        }
        
        if (ID=="02"){
            MAJ_Speed(Data);
        }

        if (ID=="05"){
            MAJ_RPM(Data);
        }

        if (ID=="06"){
            MAJ_RPM_Bar(Data.substring(0,6));

            MAJ_Led(Data.substring(3));
        }

        if (ID=="11"){
            MAJ_Bat(Data);
        }

        if (ID=="12"){
            MAJ_E_Temp(Data);
        }

        if (ID=="13"){
            MAJ_Fuel(Data);
        }

        if (ID=="14"){
            MAJ_T_Temp(Data);
        }

        if (ID=="20"){
            MAJ_Lap(Data);
        }

        if (ID=="21"){
            MAJ_D_Prev(Data.substring(0,7));
            MAJ_D_Suiv(Data.substring(8));
        }

        if (ID=="30"){
            MAJ_Best_Lap(Data);
        }

        if (ID=="31"){
            MAJ_Last_Lap(Data);
        }

        if (ID=="32"){
            MAJ_Delta_Lap(Data);
        }

        if (ID=="33"){
            MAJ_Current_Lap(Data);
        }

        if (ID=="40"){
            MAJ_Pedal(Data);
        }
    }
}
