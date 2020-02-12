// Libraries
#include "AutoX.h"

// Variables

// Function

void AutoX(){

    Serial.println("AutoX");

    Seg_1_Write(3);

    while(Finish!=1){

        if(analogRead(A6)<=384 || analogRead(A6)>640){
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
                }
            }
        }

        if(Start==1){
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
                    Finish=1;
                    Serial.println("Finish=1");
                    Serial.println(Time);
                    if(Time<1000000){
                        Seg_2_Write_Num(Time);
                        SD_Card_Write(3,Time);

                        delay(5000);
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
