CFLAGS = -mmcu=atmega328p -I. -Wall -Wstrict-prototypes -Wundef -std=gnu99 -O2

SRC=$(wildcard *.c wildcard lib/*.c)

all: $(SRC)
	avr-gcc $(CFLAGS) $^ -o $@.o
	avr-objcopy -O ihex -R .eeprom $@.o $@.hex
	avrdude -p m328p -c stk500 -P /dev/ttyACM0 -v -B2 -U flash:w:$@.hex
