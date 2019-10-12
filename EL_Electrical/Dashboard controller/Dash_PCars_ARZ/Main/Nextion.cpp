// Libraries
#include "Nextion.h"
#include <SoftwareSerial.h>

// Serial Communication

extern SoftwareSerial NextionSerial(3,2); // RX,TX
// Jaune : D2
// Bleu  : Rien

// Variables

String Color;

// Functions

void Nextion_Init(){
    NextionSerial.begin(115200);
    delay(200);
}

void MAJ_Page(int Page){
    NextionSerial.print("page ");
    NextionSerial.print(Page);
    End();
}

void End(){
    NextionSerial.write(0xff);
    NextionSerial.write(0xff);
    NextionSerial.write(0xff);
}

void MAJ_Gear(String Gear){
    NextionSerial.print("Gear.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(Gear);
    NextionSerial.print("\"");
    End();
}

void MAJ_Speed(String Speed){
    NextionSerial.print("Speed.val=");  
    NextionSerial.print(Speed); 
    End();
}

void MAJ_RPM(String RPM){
    NextionSerial.print("RPM.val=");  
    NextionSerial.print(RPM); 
    End();
}

void MAJ_RPM_Bar(String RPM_Bar){
    NextionSerial.print("Led_Strip_2.val=");  
    NextionSerial.print(RPM_Bar.substring(0,2)); 
    End();

    NextionSerial.print("Led_Strip_3.val=");  
    NextionSerial.print(RPM_Bar.substring(3)); 
    End();
}

void MAJ_Bat(String Bat){
    NextionSerial.print("Bat_Bar.val=");  
    NextionSerial.print(Bat.substring(0,2)); 
    End();

    NextionSerial.print("Bat.txt=");
    NextionSerial.print("\"");  
    NextionSerial.print(Bat.substring(3));
    NextionSerial.print("\""); 
    End();
}

void MAJ_E_Temp(String E_Temp){
    NextionSerial.print("E_Temp.txt=");
    NextionSerial.print("\"");  
    NextionSerial.print(E_Temp.substring(0,3));
    NextionSerial.print("\""); 
    End();

    NextionSerial.print("E_Temp_Bar.val=");  
    NextionSerial.print(E_Temp.substring(4)); 
    End();
}

void MAJ_Fuel(String Fuel){
    NextionSerial.print("Fuel.txt=");
    NextionSerial.print("\"");  
    NextionSerial.print(Fuel.substring(0,4));
    NextionSerial.print("\""); 
    End();

    NextionSerial.print("Fuel_B.txt=");
    NextionSerial.print("\"");  
    NextionSerial.print(Fuel.substring(5));
    NextionSerial.print("\""); 
    End();
}

void MAJ_T_Temp(String T_Temp){
    NextionSerial.print("T1_Temp.val=");  
    NextionSerial.print(T_Temp.substring(0,3));
    End();

    NextionSerial.print("T2_Temp.val=");  
    NextionSerial.print(T_Temp.substring(4,7));
    End();

    NextionSerial.print("T3_Temp.val=");  
    NextionSerial.print(T_Temp.substring(8,11));
    End();

    NextionSerial.print("T4_Temp.val=");  
    NextionSerial.print(T_Temp.substring(12,15));
    End();
}

void MAJ_Lap(String Lap){
    NextionSerial.print("N_Lap.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(Lap);
    NextionSerial.print("\"");
    End();
}

void MAJ_D_Prev(String Delta){
    NextionSerial.print("D_Prev.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(Delta);
    NextionSerial.print("\"");
    End();
}

void MAJ_D_Suiv(String Delta){
    NextionSerial.print("D_Suiv.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(Delta);
    NextionSerial.print("\"");
    End();
}

void MAJ_Best_Lap(String B_Lap){
    Color=B_Lap.substring(0,1);
      
    NextionSerial.print("B_Lap.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(B_Lap.substring(2));
    NextionSerial.print("\"");
    End();
}

void MAJ_Last_Lap(String L_Lap){
    Color=L_Lap.substring(0,1);
    Color=MAJ_Color(Color);
    
    NextionSerial.print("L_Lap.pco=");
    NextionSerial.print(Color); 
    End();
    
    NextionSerial.print("L_Lap.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(L_Lap.substring(2));
    NextionSerial.print("\"");
    End();
}

void MAJ_Current_Lap(String C_Lap){
    Color=C_Lap.substring(0,1);
    Color=MAJ_Color(Color);
    
    NextionSerial.print("C_Lap.pco=");
    NextionSerial.print(Color); 
    End();
    
    NextionSerial.print("C_Lap.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(C_Lap.substring(2));
    NextionSerial.print("\"");
    End();
}

void MAJ_Delta_Lap(String D_Lap){
    Color=D_Lap.substring(0,1);
    Color=MAJ_Color(Color);
    
    NextionSerial.print("D_Lap.pco=");
    NextionSerial.print(Color); 
    End();
    
    NextionSerial.print("D_Lap.txt=");
    NextionSerial.print("\"");
    NextionSerial.print(D_Lap.substring(2));
    NextionSerial.print("\"");
    End();
}

void MAJ_Pedal(String Pedal){
    NextionSerial.print("Throttle.val=");  
    NextionSerial.print(Pedal.substring(0,3));
    End();

    NextionSerial.print("Brake.val=");  
    NextionSerial.print(Pedal.substring(4,7));
    End();

    NextionSerial.print("Clutch.val=");  
    NextionSerial.print(Pedal.substring(8,11));
    End();

    NextionSerial.print("Steering.val=");  
    NextionSerial.print(Pedal.substring(12,15));
    End();
}

String MAJ_Color(String Color){
    if (Color=="0"){Color="57375";} // Violet
    if (Color=="1"){Color="2016";}  // Vert
    if (Color=="2"){Color="65535";} // Blanc
    if (Color=="3"){Color="65504";} // Jaune
    if (Color=="4"){Color="63488";} // Rouge
    
    return Color;
}
