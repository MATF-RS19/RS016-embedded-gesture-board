/*
 * ci2c.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#include "ci2c.h"

ci2c::ci2c() {
	// TODO Auto-generated constructor stub

}

ci2c::~ci2c() {
	// TODO Auto-generated destructor stub
}

void ci2c::init(uint8_t slave_Address) {
	//inicijalizujemo hal
	//HAL_Init();
	__HAL_RCC_I2C1_CLK_ENABLE();

	//GPIO_InitTypeDef GPIO_InitStructure;

	//koristimo i2cHandle strukturu
	slaveAddress = slave_Address;
	I2cHandle.Instance = I2C1;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.ClockSpeed = 400000;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    I2cHandle.Init.OwnAddress1 = 0;
    I2cHandle.Init.OwnAddress2 = 0;

    // inicijalizuj i2c sa parametrima iz strukture
    if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
    	trace_puts("I2C init failed");
   	    while(1);
   	}

    trace_puts("I2C init passed");

    HAL_Delay(1000);

}

void ci2c::readData(uint8_t *in, uint8_t size) {
	HAL_I2C_Master_Transmit(&I2cHandle,slaveAddress<<1,in,size,10000);
}

void ci2c::writeData(uint8_t *out, uint8_t size) {
	HAL_I2C_Master_Receive(&I2cHandle,slaveAddress<<1,out,size,10000);
}
