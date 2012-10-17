// set and clear bit
#define sbi(sfr, bit) (sfr  |=  (1<<bit))
#define cbi(sfr, bit) (sfr  &=  ~(1<<bit))

void float2string(char zieltxt[16], float zahl);
