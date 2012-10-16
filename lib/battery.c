#include <avr/io.h>

#include "analog.h"
#include "battery.h"

int battery_read() {
    uint8_t value = analog_read(MUX1);
    for (int i=0; i<7; i++) {
        if (i == 0 && value < 100) {
            return i;
        }
        if (value > (i - 1) * 22 + 99  && value < i * 22 + 100) {
            return i;
        }
        if (i == 6) {
            return i;
        }
    }
}
