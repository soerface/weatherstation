// set and clear bit
#define sbi(sfr, bit) (sfr  |=  (1<<bit))
#define cbi(sfr, bit) (sfr  &=  ~(1<<bit))

void float2string(float zahl, char zieltxt[10]);
