/*****************************************
		Datum: 16.10.2012
		Dateien: winsensor.h/windsensor.c
*******************************************/
#define ANEMO_DDR DDRB
#define ANEMO_PIN PINB
#define ANEMO_PORT PB0

void  anemometer_init(void);
float anemometer_read(void);
