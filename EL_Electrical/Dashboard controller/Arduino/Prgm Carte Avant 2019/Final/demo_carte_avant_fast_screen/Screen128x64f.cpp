/***************************************************************************
   
   Function name: Grear_Update
   
   Author:        Martín Gómez-Valcárcel (MGV)
   
   Descriptions:  Grear_Update receives the gear the engine is in and, from
                  PINS_GEAR, determines which segments it has to illuminate
                  so that the pilot knows the gear he's in.
                            
***************************************************************************/
#include "Screen128x64.h"
//#include "U8glib.h"

/**************************************************************************/
//    Internal variables and constants used ONLY by the functions in this file
/**************************************************************************/

//U8GLIB_ST7920_128X64_1X u8g(23, 17, 16,U8G_PIN_NONE);
//U8GLIB_ST7920_128X64_4X u8g(23, 17, 16,U8G_PIN_NONE);
/**************************************************************************/
//    Functions
/**************************************************************************/
#define LCD_SID  17
#define LCD_SCLK 23
#define LCD_CS 16

void lcd_send(bool value) {
  digitalWrite(LCD_SID, value);
  digitalWrite(LCD_SCLK, HIGH);
  digitalWrite(LCD_SCLK, LOW);
}


void lcd_sync(bool rs, bool rw) {
  lcd_send(1); // Sync 1
  lcd_send(1); // Sync 2
  lcd_send(1); // Sync 3
  lcd_send(1); // Sync 4
  lcd_send(1); // Sync 5
  lcd_send(rw);
  lcd_send(rs);
  lcd_send(0);
}

void lcd_data(uint8_t data) {
  lcd_send(data & 0b10000000);
  lcd_send(data & 0b01000000);
  lcd_send(data & 0b00100000);
  lcd_send(data & 0b00010000);
  lcd_send(0);
  lcd_send(0);
  lcd_send(0);
  lcd_send(0);
  lcd_send(data & 0b00001000);
  lcd_send(data & 0b00000100);
  lcd_send(data & 0b00000010);
  lcd_send(data & 0b00000001);
  lcd_send(0);
  lcd_send(0);
  lcd_send(0);
  lcd_send(0);
}

void lcd_cmd(uint8_t cmd) {
  lcd_sync(0, 0); // All commands have rs=0 and rw=0
  lcd_data(cmd);
  delayMicroseconds(72); // The datasheet specifies that commands take 72u to execute
}

void lcd_extended_function_set(bool extended, bool graphics) {
  lcd_cmd(  0b00100000 | (extended   ? 0b00000100 : 0) |(graphics   ? 0b00000010 : 0));
}

void lcd_display_status(bool display_on, bool cursor_on, bool blink_on) {
  lcd_cmd(0b00001000 |
    (display_on ? 0b0100 : 0) |
    (cursor_on  ? 0b0010 : 0) |
    (blink_on   ? 0b0001 : 0)
  );
}

void lcd_clear() {
  lcd_cmd(0b00000001);
  delayMicroseconds(1600); // The datasheet specifies that CLEAR requires 1.6ms
}

void lcd_write_begin() {
  lcd_sync(1,0);
}

void lcd_write_byte(uint8_t w) {
  lcd_data(w);
}
void lcd_set_ddram_address(uint8_t addr) {
  lcd_cmd(0b10000000 | (addr & 0b00111111));
}


void lcd_write_int(int num, int sizeOfInt) {
  char numLettre[sizeOfInt];
  itoa ( num, numLettre, 10);
  for (int i = 0; i<sizeOfInt; i++){
    lcd_write_byte(numLettre[i]);
  }
}

void lcd_write_str(const char *str) {
  char c = pgm_read_byte_near(str++);
  while(c) {
     lcd_write_byte(c);
     c = pgm_read_byte_near(str++);
  }
}

void lcd_write_word(uint16_t w) {
  lcd_data((w >> 8) & 0xFF);
  lcd_data((w >> 0) & 0xFF);
}




// ================== INIT ======================

void Screen_Init_Fast(){

  unsigned long StartTime;
  StartTime = millis();
  
  Serial.println("start");
  pinMode(LCD_CS,  OUTPUT);
  digitalWrite(LCD_CS, HIGH);
  pinMode(LCD_SID,  OUTPUT);
  pinMode(LCD_SCLK, OUTPUT);

  // Initialize the display
  lcd_extended_function_set(false, true); // Do this twice since only one bit
  lcd_extended_function_set(false, true); // can be set at a time.
  lcd_display_status(true, false, false);
  lcd_clear();

  Serial.println(millis() - StartTime);
}







// ====================== LOOP ==================

void Screen_Update_Fast(signed Gear, int W_Temp, int Volts){
  unsigned long StartTime;
  StartTime = millis();
  
  lcd_extended_function_set(false, false); // Do this twice since only one bit
  lcd_extended_function_set(false, false); // can be set at a time.
  lcd_display_status(true, false, false);

  
  lcd_set_ddram_address(0x18);   
  lcd_write_begin();
  if (W_Temp < 100) {
    lcd_write_int(W_Temp,2);
    lcd_write_str(PSTR("C "));
  } else {
    lcd_write_int(W_Temp,3);
    lcd_write_str(PSTR("C"));
  }
  
    
  lcd_set_ddram_address(0x1D);   
  lcd_write_begin();
  lcd_write_int(Volts,2);
  lcd_write_str(PSTR("."));
  lcd_write_int(Volts%10,1);
  lcd_write_str(PSTR("V"));
  Serial.println(millis() - StartTime);
}







/***************************************************************************
  END FILE
***************************************************************************/
