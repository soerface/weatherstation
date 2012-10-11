all:
	avr-gcc -mmcu=atmega328p -I. -Wall -Wstrict-prototypes -Wundef -std=gnu99 main.c lcd/lcd.c -O2 -o main.o
	avr-objcopy -O ihex -R .eeprom main.o main.hex
	avrdude -p m328p -c stk500 -P /dev/ttyACM0 -v -B2 -U flash:w:main.hex
