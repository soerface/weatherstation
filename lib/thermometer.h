#define LM75_ADDR 0x4F
#define F_CPU    8000000
#define F_SCL 100000
#define TWI_PRESC 1
#define TWBR_VAL (F_CPU / F_SCL - 16) / (2 * TWI_PRESC)
#define TW_BUSY_WAIT() while( !(TWCR & (1<<TWINT)))
#define CHECK_TW_ERROR(ecode)  status = TW_STATUS; \
    if (status != ecode) return (status >> 3)

void thermometer_init(void);
int thermometer_read(void);
