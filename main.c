#define F_CPU    8000000

#include <avr/io.h>
#include <util/delay.h>

#include "lib/lcd.h"

int main(void)
{
    _delay_ms(50);
    lcd_init();

    int i = 6;
    while (1)
    {
        lcd_set_battery_level(i);
        lcd_set_label("Temperatur", "15.5 C");
        _delay_ms(50);
        lcd_set_label("Druck", "n Pascal");
        _delay_ms(50);
        i--;
    }
}
