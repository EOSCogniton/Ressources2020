// Libraries
#include "SegDisp.h"
#include "SevenSegmentTM1637.h"

// Pinout
const byte CLK=7;
const byte DIO1=8;
const byte DIO2=9;

// Variables

String Str;
String Seg1;
String Seg2;
String Seg3;
String Seg4;

// Function

// Display
SevenSegmentTM1637    Disp1(CLK, DIO1);
SevenSegmentTM1637    Disp2(CLK, DIO2);

void Seg_Init(){
    // Display 1 
    Disp1.begin();
    Disp1.setBacklight(100);
    Disp1.clear();

    // Display 2
    Disp2.begin();
    Disp2.setBacklight(100);
    Disp2.clear();
}

void Seg_1_Write(int i){
    if(i==1){Disp1.print("Acc ");} 
    if(i==2){Disp1.print("Shid");}
    if(i==3){Disp1.print("AutX");}
    if(i==4){Disp1.print("End ");}
}

void Seg_2_Write_Run(){
    Disp2.print("Run ");
}

void Seg_2_Write_Clear(){
    Disp2.clear();
}

void Seg_2_Write_Num(unsigned long Time){
    Str= (String) Time;
    if(Time<10000){ // Time<10s
        Seg1=Str[0]; Seg2="_"; Seg3=Str[1]; Seg4=Str[2];
        Disp2.print(Seg1+Seg2+Seg3+Seg4);
    }
    if(Time>=10000 && Time<100000){
        Seg1=Str[0]; Seg2=Str[1]; Seg3="_"; Seg4=Str[2];
        Disp2.print(Seg1+Seg2+Seg3+Seg4);
    }
    if(Time>=100000 && Time<1000000){
        Seg1=Str[0]; Seg2=Str[1]; Seg3=Str[2]; Seg4="_";
        Disp2.print(Seg1+Seg2+Seg3+Seg4);
    }

}
