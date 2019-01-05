/*
 * ci2c.h
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#ifndef CI2C_H_
#define CI2C_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include "diag/Trace.h"

class ci2c {
public:
	ci2c();

	void init(uint8_t slave_Address);
	void readData(uint8_t *in, uint8_t size);
	void writeData(uint8_t *out, uint8_t size);

	virtual ~ci2c();

private:
	I2C_HandleTypeDef I2cHandle;
	uint8_t slaveAddress;

};

#endif /* CI2C_H_ */
