// Libraries
#include "Accel.h"
#include "Arduino.h"
#include "End.h"
#include "SegDisp.h"

// Variables
String Data;

// Function

void Accel(){

    // Affichage de "Acc" sur le 1er 7 Seg

    // Début du code
    while(Finish!=1){

        // Si Start==0
        if(Start==0){
            // Allumage de la LED de détection si réception d'un signal d'un détecteur
            if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                Detection=1
                digitalWrite(,255);
            } else {
                Detection=0
                digitalWrite(,0);
            }
    
            // Démarrage du chrono si possible
            if(Detection==0 && digitalRead(A0)==HIGH){
                Start=1;

                delay(200);
            }
        }

        // Si Start==1
        if(Start==1){
            if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                // Démarrage du chrono
                Instant=millis();

                // Affichage de "Run" sur le 2ème 7 Seg

                delay(1000);
            }

            while(Finish!=1){
              
                if(digitalRead(5)==HIGH || digitalRead(6)==HIGH){
                    // Fin du chrono
                    Time=millis()-Instant;

                    // Conversion de Time en String ("Data")
                    Data=String(Time)

                    // Affichage du temps sur le 2ème 7 Seg

                    // On enregistre le temps sur la SD
                    SD_Card_Write(int 1, String Data)

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
