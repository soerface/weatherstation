#include <avr/io.h>
#include "barometer.h"
#include "analog.h"

float barometer_read()
{
	float ausgang;
	float Vout;
	float pressure;
	
	ausgang = (float) analog_read(MUX0);			// Zurückgegebenes Int in Float umwandeln
	Vout= ((5*ausgang)/255);					// gelesener Wert in V umwandeln
	pressure=((((Vout/5.1)+0.1518)/0.01059)*10); //Formel aus Datenblatt zum Berechnen des Druckwert in hPa
	return(pressure);	
}
