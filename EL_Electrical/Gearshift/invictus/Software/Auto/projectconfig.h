/**************************************************************************/
/*!
    @file     projectconfig.h
    @author   Bruno Moreira Nabinger and Corentin Lepais (EPSA)
                                                  Ecurie Piston Sport Auto
    
    Config settings and macros in this header file,  for controling the 
    Motor with integrated Controller and CAN interface BG 45 CI.

 
    @section  HISTORY
    
    v0.1 - 10/11/2018 First release ()
*/
/**************************************************************************/

//inclusion guards - ensure this file definitions are only ever included
//once 
#ifndef INC_PROJECTCONFIG_H //if not define symbol INC_PROJECTCONFIG_H
#define INC_PROJECTCONFIG_H 


//--------------  assignation des pins  ------------------
/* PIN Mapping    
     cf epsabox: https://epsabox.kad-office.com/w/CCD_20_S23
      */
const int paletteDecrease = 0; //palette de gauche
const int paletteIncrease = 1; //palette de droite
const int motorState1 = 8; 
const int motorState2 = 9; 
const int chipSelect = 10;
const int pinLED = 13;
const int wetDry = 14;
const int launchControl = 15;
const int tractionControl=16;
const int logDta=17;
const int shiftCut = 18; 
const int motorInput0 = 22;
const int motorInput1 = 21;
const int motorInput2 = 20;
const int motorInput3 = 19;
const int gearPot = A14;

#endif  /* inclusion guards - INC_PROJECTCONFIG_H */ 

// SIZER, Ben. Organizing Code Files in C and C++.  
// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/organizing-code-files-in-c-and-c-r3173
// June 8, 2013. Last Access 10 nov 2018.

// TOWNSEND, Kevin. KTOWN's Guide to Readable C Code.
// https://cdn-learn.adafruit.com/downloads/pdf/ktowns-guide-to-readable-c-code.pdf
// Last Access 10 nov 2018.
