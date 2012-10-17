#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lib/analog.h"
#include "lib/anemometer.h"
#include "lib/barometer.h"
#include "lib/battery.h"
#include "lib/lcd.h"
//#include "lib/thermometer.h"
#include "lib/utils.h"

int selection = 0;

ISR(INT0_vect)
{
    cli();
    PORTB ^= (1<<PD5);
    //lcd_set_label("INT", "ETERUPT!");
    //lcd_update();
    //_delay_ms(50);
    selection = ++selection % 2;
    entprellung(&PIND, (1<<PIND2));
    sei();
}

void init(void) {
    analog_init();
    anemometer_init();
    //battery_init();
    lcd_init();

    cbi(DDRD, PD2);
    //DDRD = 0x00;

    sbi(EICRA, ISC00);
    sbi(EICRA, ISC01);
    sbi(EIMSK, INT0);

    sei();
}

int main(void)
{
    char buf[16];
    char labels[2][16] = {
        "Luftdruck",
        "Windgeschw.",
    };
    char units[2][16] = {
        "Pa",
        "m/s",
    };
    float (*functions[2]) () = {
        barometer_read,
        anemometer_read,
    };

    init();
    while(1)
    {
        lcd_set_battery_level(battery_read());
        float2string(buf, functions[selection]());
        sprintf(buf, "%s %s", buf, units[selection]);
        lcd_set_label(labels[selection], buf);
        lcd_update();
    }
    return 0;
}

void entprellung(volatile uint8_t *port, uint8_t maske) {
    uint8_t port_puffer;
    uint8_t entprellungs_puffer;

    for (entprellungs_puffer=0; entprellungs_puffer!=0xff; ) {
        entprellungs_puffer <<= 1;
        port_puffer = *port;
        _delay_us(500);
        if( (*port & maske) == (port_puffer & maske) ) {
            entprellungs_puffer |= 0x01;
        }
    }
}
