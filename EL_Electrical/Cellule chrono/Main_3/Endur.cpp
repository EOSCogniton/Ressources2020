// Libraries
#include "Endur.h"

// Variables

// Function

void Endur(){

    Serial.println("Endur");

    Seg_1_Write(4);

    while(Finish!=1){

        if(analogRead(A6)<=640 || analogRead(A6)>896){
            Seg_2_Write_Clear();
            break;
        }

        if(Start==0){
            if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                Serial.println("Detection");
                delay(100);                
            } else {
                if(digitalRead(A0)==HIGH){
                    Start=1;
                    Serial.println("Start=1");

                    delay(2000);
                }
            }
        }

        if(Start==1){
          
            if(digitalRead(A0)==HIGH){
                Finish=1;
            }
            
            if(Run==0){
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    Instant=millis();
                    Run=1;                
                    Serial.println("Run=1");
                    Serial.println(Instant);
                    Seg_2_Write_Run();
                    delay(1000);
                }
            }
  
            if(Run==1){
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    Time=millis()-Instant;
                    Instant=millis();

                    Serial.println(Time);
                    if(Time<1000000){
                        Seg_2_Write_Num(Time);
                        SD_Card_Write(4,Time);

                        delay(1000);
                    } else {
                        break;
                    }
                }
            }
        }
    }

    // On termine le programme
    End();
}

        
