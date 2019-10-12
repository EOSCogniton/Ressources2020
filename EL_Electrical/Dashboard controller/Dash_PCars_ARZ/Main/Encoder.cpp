// Libraries
#include "Encoder.h"
#include "Nextion.h"

// Pin Out

const int SW_E=4;
const int DT_E=5;
const int CLK_E=6;

// Variables

int State;
int State_B;
int Count=0;

int Switch;
int Switch_B;

// Functions

void Encoder_Init(){
    pinMode(CLK_E,INPUT);
    pinMode(DT_E,INPUT);
    pinMode(SW_E,INPUT);
    
    State_B=digitalRead(CLK_E);
    Switch_B=digitalRead(SW_E);
}

void Button(){
    // Switch==0 -> Pressed
    // Switch==1 -> Released

    Switch=digitalRead(SW_E);
    
    if(Switch==0){
        if(Switch!=Switch_B){
            Switch_B=0;
            // Page -> Selector
            MAJ_Page(1);
            Page=1;
            delay(50);
        }
    } 
    
    if(Switch!=0){
        Switch_B=Switch;
    }
}

void Rotary(){
    State=digitalRead(CLK_E);

    if(State>State_B){
        
        if(digitalRead(DT_E)!=State){
            Count++;
            delay(100);
        }else{
            Count--;
            delay(100);
        }
        Count=min(3,max(2,Count));
        MAJ_Page(Count); 
    }

    if(State!=State_B){
        State_B=State;
    }    
}
