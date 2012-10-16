#define LCDPORT       PORTD
#define LCDDDR        DDRD
#define LCDDDR_PORT   0xFB
#define LCD_PIN_RS    0
#define LCD_PIN_E     1
#define LCD_PIN_D4    3
#define LCD_PIN_D5    4
#define LCD_PIN_D6    5
#define LCD_PIN_D7    6
#define LCD_SETDDRAM  0x80 // Set Display RAM Address

/***** LCD STEUERBEFEHLE *****/

#define LCD_CLEAR     0x01 // Display löschen
#define LCD_HOME      0x02 // Cursor an den Anfang zurück
#define LCD_ON        0x0C // 0x0C = LCD ON, Cursor OFF
#define LCD_OFF       0x08 // Display OFF

/***** HILFSDEFINITIONEN *****/

#define CMD           0
#define DATA          1
#define sbi(sfr, bit) (sfr  |=  (1<<bit))
#define cbi(sfr, bit) (sfr  &=  ~(1<<bit))


void lcd_clear(void);
void lcd_init(void);
void lcd_generate_char(uint8_t code, const uint8_t *data);
void lcd_generate_chars(void);
void lcd_send(unsigned char type, unsigned char c);
// Set the battery level, from 0 (empty) to 6 (full)
void lcd_set_battery_level(int level);
// Writes label and value on the display, e.g. lcd_set_label("Temperature", "15.5 °C")
void lcd_set_label(char *k, char *v);
// Switch to line `pos`
void lcd_set_line(int pos);
// Switch to position `posx` `posy`
void lcd_set_pos(int posx, int posy);
// Display the current data
void lcd_update(void);
void lcd_write(char *t);
