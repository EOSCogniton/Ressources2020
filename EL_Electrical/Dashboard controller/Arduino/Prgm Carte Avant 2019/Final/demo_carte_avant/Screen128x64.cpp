/***************************************************************************
   
   Function name: Grear_Update
   
   Author:        Martín Gómez-Valcárcel (MGV)
   
   Descriptions:  Grear_Update receives the gear the engine is in and, from
                  PINS_GEAR, determines which segments it has to illuminate
                  so that the pilot knows the gear he's in.
                            
***************************************************************************/
#include "Screen128x64.h"
#include "U8glib.h"


/**************************************************************************/
//    Internal variables and constants used ONLY by the functions in this file
/**************************************************************************/

U8GLIB_ST7920_128X64_1X u8g(23, 17, 16,U8G_PIN_NONE);

/**************************************************************************/
//    Functions
/**************************************************************************/

void u8g_prepare(void) {
  u8g.setFont(u8g_font_courB08r);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

    
void Screen_Init(){
  const byte cx = 21;
  const byte cy = 15;

  for (int i = 0; i<= 10; i++){
    u8g.firstPage();
    do {

      //E
      u8g.drawBox(cx+5,cy,i,5);
      u8g.drawBox(cx+5,cy+10,i,5);
      u8g.drawBox(cx+5,cy+20,i,5);
      u8g.drawBox(cx,cy,5,25);

      //P
      u8g.drawBox(cx+25,cy,i,5);
      u8g.drawBox(cx+25,cy+10,i,5);
      u8g.drawBox(cx+35,cy+5,i/2,5);
      u8g.drawBox(cx+20,cy,5,25);

      //S
      u8g.drawBox(cx+50,cy,i,5);
      u8g.drawBox(cx+45,cy+10,i,5);
      u8g.drawBox(cx+45,cy+20,i,5);
      u8g.drawBox(cx+45,cy,5,15);
      u8g.drawBox(cx+55,cy+10,5,15);

      //A
      u8g.drawBox(cx+70,cy,i,5);
      u8g.drawBox(cx+70,cy+10,i,5);
      u8g.drawBox(cx+65,cy,5,25);
      u8g.drawBox(cx+80,cy,5,25);

      //Barre
      u8g.drawBox(cx,cy+30,8*i+5,3);

    } while( u8g.nextPage() ); 
  }
  delay(1000);
}


void Draw_Float(int xcoord, int ycoord, float var, int nbchar){
  char b[nbchar+1];
  String(var).toCharArray(b,nbchar+1);
  u8g.drawStr(xcoord,ycoord,b);
} 

void Draw_Int(int xcoord, int ycoord, int var, int nbchar){
  char b[nbchar+1];
  String(var).toCharArray(b,nbchar+1);
  u8g.drawStr(xcoord,ycoord,b);
} 

void Screen_Update(signed Gear, int W_Temp, int Volts){
  u8g.firstPage();  
  do {
    u8g_prepare();
    u8g.setFont(u8g_font_fub35n);
    Draw_Int(55,40,Gear,1);
    
    u8g.setFont(u8g_font_courB08r);
    
    Draw_Int(0,64,W_Temp,3);
    u8g.drawStr(0,64,"   C");

    Draw_Float(98,64,(float) Volts/10,4);
    u8g.drawStr(98,64,"    V");
  } while( u8g.nextPage()); 
}



/***************************************************************************
  END FILE
***************************************************************************/
