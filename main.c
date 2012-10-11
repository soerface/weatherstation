#define F_CPU    8000000

#include <avr/io.h>
#include <util/delay.h>

#include "lcd/lcd.h"

int main(void)
{
    _delay_ms(50);
    lcd_init();
    lcd_write("Starting LCD...");

    while (1)
    {
        lcd_clear();
        lcd_set_label("Temperatur", "15.5 C");
        _delay_ms(200);
        lcd_set_label("Druck", "n Pascal");
        _delay_ms(200);
    }
}
