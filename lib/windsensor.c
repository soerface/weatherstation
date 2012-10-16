/*같같같같같같같같같같같같같같같같같같같같
		Datum: 16.10.2012
		Dateien: winsensor.h/windsensor.c
같같같같같같같같같같같같같같같같같같같같같*/
#include <avr/interrupt.h>
#include <stdio.h>

#include "utils.h"

volatile unsigned int millisekunden;
volatile int i, state = 0;
volatile float val;
char txt[10];

void anemometer_init()
{
	//ANEMO_DDR = ~(1<<PB0);
        cbi(ANEMO_DDR, ANEMO_PORT);

	TCNT0 = 0;
	//TCCR0A |= (1<<WGM01);
        sbi(TCCR0A, WGM01);
	OCR0A = 125;
	//TIMSK0 |= (1<<OCIE0A);
        sbi(TIMSK0, OCIE0A);
	sei();
	//TCCR0B |= (1<<CS01);
        sbi(TCCR0B, CS01)
}

float anemometer_read()
{
	return val;
}

ISR(TIMER0_COMPA_vect)
{
	if (state == 0 && (ANMEO_PIN & (0x01)))
	{
		state = 1;
		i++;
	}
	else if (state == 1 && (!(ANMEO_PIN & (0x01))))
	{
		state = 0;
	}

	millisekunden++;
	if(millisekunden==1000)
	{
		val = i*0.4;
		millisekunden = 0;
		i = 0;
	}
}
