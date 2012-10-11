/****************************************************************
*  LCD Ausgabe für Hitachi HD44780 kompatible LCD Controller
*
*  Mikroontroller:  AT90PWM316
*  Clock:      8MHz intern
*  LCD-Display:  Displaytech 162B
*  LCD-Controller:  KS0070B
*
*  Konfiguration:  PORT D7 = LCD D7
*           PORT D6 = LCD D6
*           PORT D5 = LCD D5
*           PORT D4 = LCD D4
*          PORT D3 = LCD E
*          PORT D2 = LCD RS
*          GND    = LCD Vss + LCD R/W  + LCD K
*          +5V    = LCD Vdd
*          Poti  = LCD V0
*  +5V (über R = 1kOhm)  = LCD A
****************************************************************/


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void lcd_clear() {
    lcd_send(CMD, LCD_CLEAR);
}

void lcd_generate_char(uint8_t code, const uint8_t *data)
{
    // Startposition des Zeichens einstellen
    lcd_send(CMD, 0x40|(code<<3));

    // Bitmuster übertragen
    for (uint8_t i=0; i<8; i++)
    {
        lcd_send(DATA, data[i]);
    }
}

void lcd_generate_chars() {
    lcd_send(CMD, 0x40|(0<<3));
    // custom character data: °, Battery full, Battery
    uint8_t data[8][8] = {
        {0b00110, 0b01001, 0b01001, 0b00110, 0b00000, 0b00000, 0b00000, 0b00000},
        {0b01110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},
        {0b01110, 0b11011, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},
        {0b01110, 0b11011, 0b10001, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},
        {0b01110, 0b11011, 0b10001, 0b10001, 0b11111, 0b11111, 0b11111, 0b11111},
        {0b01110, 0b11011, 0b10001, 0b10001, 0b10001, 0b11111, 0b11111, 0b11111},
        {0b01110, 0b11011, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111, 0b11111},
        {0b01110, 0b11011, 0b10101, 0b10101, 0b10001, 0b10101, 0b10001, 0b11111},
    };
    for (uint8_t i=0; i<8; i++) {
        lcd_generate_char(i, data[i]);
    }
}

void lcd_init()
{
/* Port auf Ausgang schalten */
  LCDPORT = 0x00;
  LCDDDR  = 0xFF;

  _delay_ms(40); // Warten bis LCD bereit ...

/* 4-bit Modus konfigurieren ------Function-Set 1*/
  sbi(LCDPORT, LCD_PIN_D5);
  cbi(LCDPORT, LCD_PIN_D4);

  _delay_ms(40);
/* 4-bit Modus konfigurieren ------Function-Set 2*/
  sbi(LCDPORT, LCD_PIN_D5);
  cbi(LCDPORT, LCD_PIN_D4);

  _delay_ms(5);
/* 4-bit Modus konfigurieren ------Function-Set 3*/
  sbi(LCDPORT, LCD_PIN_D5);
  cbi(LCDPORT, LCD_PIN_D4);

/* 4-Bit Modus starten ... */
  sbi(PORTD, LCD_PIN_E);
  cbi(PORTD, LCD_PIN_E);
  _delay_ms(5);

/* 2 Zeilen, 4-Bit Modus */
  lcd_send(CMD, 0x28);
  //lcd_send(CMD, 0x14);

  lcd_send(CMD, LCD_OFF);
  lcd_send(CMD, LCD_CLEAR);

  lcd_send(CMD, 0x06);
  lcd_send(CMD, LCD_ON);
  lcd_generate_chars();
  lcd_clear();
}

void lcd_send(unsigned char type, unsigned char c)
{
  if (type==CMD)
    cbi(LCDPORT, LCD_PIN_RS); /* RS=0: Befehl folgt ... ******/
  else
    sbi(LCDPORT, LCD_PIN_RS); /* RS=1: Daten folgen ... ******/

  /* (1) HIGH NIBBLE wird gesendet ******/
  if (bit_is_set(c, 7))
    sbi(LCDPORT, LCD_PIN_D7);
  else cbi(LCDPORT, LCD_PIN_D7);

  if (bit_is_set(c, 6))
    sbi(LCDPORT, LCD_PIN_D6);
  else cbi(LCDPORT, LCD_PIN_D6);

  if (bit_is_set(c, 5))
    sbi(LCDPORT, LCD_PIN_D5);
  else cbi(LCDPORT, LCD_PIN_D5);

  if (bit_is_set(c, 4))
    sbi(LCDPORT, LCD_PIN_D4);
  else cbi(LCDPORT, LCD_PIN_D4);

  /* Flanke zur Übernahme der Daten senden ... ******/
  sbi(LCDPORT, LCD_PIN_E);
  _delay_ms(1);
  cbi(LCDPORT, LCD_PIN_E);

  /* (2) LOW NIBBLE wird gesendet ******/
  if (bit_is_set(c, 3))
    sbi(LCDPORT, LCD_PIN_D7);
  else cbi(LCDPORT, LCD_PIN_D7);

  if (bit_is_set(c, 2))
    sbi(LCDPORT, LCD_PIN_D6);
  else cbi(LCDPORT, LCD_PIN_D6);

  if (bit_is_set(c, 1))
    sbi(LCDPORT, LCD_PIN_D5);
  else cbi(LCDPORT, LCD_PIN_D5);

  if (bit_is_set(c, 0))
    sbi(LCDPORT, LCD_PIN_D4);
  else cbi(LCDPORT, LCD_PIN_D4);

  /* Flanke zur Übernahme der Daten senden ... ******/
  sbi(LCDPORT, LCD_PIN_E);
  _delay_ms(1);
  cbi(LCDPORT, LCD_PIN_E);

  /* (3) Auf den LCD Controller warten ...******/
  _delay_ms(5);
}

void lcd_set_label(char *k, char *v) {
    lcd_clear();
    lcd_write(k);
    lcd_set_line(1);
    lcd_write(v);
}

void lcd_set_line(int pos) {
    lcd_send(CMD, LCD_SETDDRAM +0x40);  //Cursor auf 1.Position Zeile 2
}

void lcd_set_pos(int posx, int posy) {

}

void lcd_write(char *t)
{
  for (uint8_t i=0; i<255; i++)
  {
    if (t[i]=='\0') {
      return;
    }
    // insert custom characters
    else if (t[i] == 'C' && t[i-1] == ' ' && t[i+1] == '\0') {
        lcd_send(DATA, 0);
        lcd_send(DATA, 'C');
    }
    else {
      lcd_send(DATA, t[i]);
    }
  }
}
