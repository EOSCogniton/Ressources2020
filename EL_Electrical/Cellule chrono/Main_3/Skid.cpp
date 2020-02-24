// Libraries
#include "Skid.h"

// Variables

unsigned long Time1;
unsigned long Time2;


// Function

void Skid(){

    Serial.println("Skid");

    Seg_1_Write(2);

    while(Finish!=1){

        if(analogRead(A6)<=128 || analogRead(A6)>384){
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
                    Run=1;                
                    Serial.println("Run=0");
                    Seg_2_Write_Run();
                    delay(1000);
                }
            }

            if(Run==1){
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    Instant=millis();
                    Run=2;
                    Serial.println("Run=1");
                    Serial.println(Instant);
                    delay(1000);
                }
            }
  
            if(Run==2){
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    Time1=millis()-Instant;
                    Run=3;
                    Serial.println("Run=2");
                    Serial.println(Time1);
                    if(Time1>=1000000){
                        break;
                    }
                    delay(1000);                    
                }
            }

            if(Run==3){
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    Instant=millis();
                    Run=4;                
                    Serial.println("Run=3");
                    Serial.println(Instant);
                    delay(1000);
                }
            }

            if(Run==4){
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    Time2=millis()-Instant;
                    Serial.println("Run=4");
                    Serial.println(Time2);
                    if(Time2>=1000000){
                        break;
                    }
                    Finish=1;
                    Serial.println("Finish=1");
                    Time=(Time1+Time2)/2;
                    Serial.println(Time);
                    Seg_2_Write_Num(Time);
                    SD_Card_Write(2,Time,Time1,Time2);

                    delay(5000);
                }
            }
        }  
    }

    // On termine le programme
    End();
}
