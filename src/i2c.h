#include <stdint.h>

void initI2c();

void i2cApi_write(uint8_t* in, uint8_t len);
void i2cApi_read(uint8_t* out, uint8_t len);
