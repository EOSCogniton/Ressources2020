// Libraries
#include "Accel.h"


// Variables

// Function

void Accel(){

    // Affichage de "Acc" sur le 1er 7 Seg

    // Début du code
    while(Finish!=1){

        // Si Start==0
        if(Start==0){
          
            Serial.print("Start : ");
            Serial.println(Start);
            
            // Allumage de la LED de détection si réception d'un signal d'un détecteur
            if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                Detection=1;
                digitalWrite(A1,255);
            } else {
                Detection=0;
                digitalWrite(A1,0);
            }

            Serial.print("Detection : ");
            Serial.println(Detection);
    
            // Démarrage du chrono si possible
            if(Detection==0 && digitalRead(A0)==HIGH){
                Start=1;
                
                Serial.print("Start : ");
                Serial.println(Start);
                
                delay(200);
            }
        }

        // Si Start==1
        if(Start==1){
            if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                // Démarrage du chrono
                Instant=millis();
                
                Serial.print("Instant : ");
                Serial.println(Instant);

                // Affichage de "Run" sur le 2ème 7 Seg

                delay(1000);
            }

            while(Finish!=1){
              
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    // Fin du chrono
                    Time=millis()-Instant;
                    
                    Serial.print("Time : ");
                    Serial.println(Time);

                    // Affichage du temps sur le 2ème 7 Seg

                    // On enregistre le temps sur la SD
                    SD_Card_Write(1, Time);

                    // Fin du Run
                    Finish=1;
                }

                // Arret du chrono par bouton
                if(digitalRead(A0)==HIGH){
                    Finish=1;

                    // Affichage de "Stop" sur le 2ème 7 Seg
                }
            }
        }
    }
    
    // On termine le programme
    End();
}
