#include <stdint.h>

// slave address
#define I2C_ADDRESS 0x42

void initI2c();

void i2cApi_write(uint8_t* in, uint8_t len);
void i2cApi_read(uint8_t* out, uint8_t len);
