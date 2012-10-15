#include <avr/io.h>
#include "analog.h"

void analog_init()// Initialisieren des analogen Eingangs
{
	DDRC=0x00;
	uint8_t adc = 0;
	ADCSRA |= (1<<ADPS2);  // 128: Vorteiler
	ADCSRA |= (1<<ADPS1);	
	ADCSRA |= (1<<ADPS0);
	ADCSRA = (1<<ADEN);
	ADCSRA |= (1<<ADSC);

	while(ADCSRA & (1<<ADSC)){}
	adc=ADCH;
}

int analog_read(int channel)
{
	ADMUX &= 0xF0; // Kanal zurücksetzen
	
	switch (channel) //Kanal auswählen
	{
		case 1:				//PC1 Barometer
		{
			ADMUX |= (1<<MUX0);
			break;
		}
		case 2:				//PC2 Batterie
		{
			ADMUX |= (1<<MUX1);
			break;
		}
		default:				//PC3 Batterie
		{
			break;
		}
	}
	ADMUX |= (1<<REFS0); //AVCC als Referenz (hier: 5 bzw. 0V)
	ADMUX |= (1<<ADLAR); // links anfangen
	ADCSRA |= (1<<ADSC); // Starten der Wandlung
	while (ADCSRA & (1<<ADSC)) {}	// Warten bis Wandlung zu Ende ist
	return (ADCH);

}
