#include <avr/io.h>

#include "analog.h"
#include "battery.h"

int battery_state() {
    analog_read(MUX1);
    for (int i=0; i<7; i++) {
        if (i == 0 && ADCH < 100) {
             return i;
        }
        if (i == 6 && ADCH < 210) {
             return i;
        }
        if (ADCH > (i - 1) * 22 + 99  && ADCH < i * 22 + 100) {
            return i;
        }
    }
}
