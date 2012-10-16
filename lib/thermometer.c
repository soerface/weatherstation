#include <avr/io.h>
#include <util/twi.h>

#include "thermometer.h"

#define sbi(sfr, bit) (sfr  |=  (1<<bit))
#define cbi(sfr, bit) (sfr  &=  ~(1<<bit))

void thermometer_init() {
    //TWBR = TWBR_VAL;
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);    //start
    loop_until_bit_is_set(TWCR, TWINT);
    TWDR = LM75_ADDR;                    //adresse eingeben
    TWCR = (1<<TWINT) | (1<<TWEN);            //freigeben (senden)
    loop_until_bit_is_set(TWCR, TWINT);
}

int thermometer_read() {
    uint8_t ret_val, status;    //return-wert, temp. Variable fuer TWSR

    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    TW_BUSY_WAIT();
    TWDR = (LM75_ADDR << 1 ) | TW_READ;
    TWCR = (1<<TWINT) | (1<<TWEN);
    TW_BUSY_WAIT();
    CHECK_TW_ERROR(TW_MR_SLA_ACK);

    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN); //read and send ACK
    TW_BUSY_WAIT();
    status = TW_STATUS;
    CHECK_TW_ERROR(TW_MR_DATA_ACK);
    ret_val = TWDR<<8; //get highbyte

    TWCR = (1<<TWINT) | (1<<TWEN);  // read and send NAK
    TW_BUSY_WAIT();
    CHECK_TW_ERROR(TW_MR_DATA_NACK);
    ret_val |= TWDR;    //get low-byte
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
    return ret_val;







    sbi(TWCR, TWINT);
    sbi(TWCR, TWSTA);
    sbi(TWCR, TWEN);
    while (!(TWCR & (1<<TWINT)));
    /*if ((TWSR & 0xF8) != TW_START) {
        //ERROR();
    }*/
    TWDR = LM75_ADDR;
    TWCR = (1<<TWINT) | (1<<TWEN);
    sbi(TWCR, TWINT);
    sbi(TWCR, TWEN);
}
