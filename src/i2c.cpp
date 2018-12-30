#include <stm32f4xx_hal.h>
#include "diag/Trace.h"
#include <stdint.h>

I2C_HandleTypeDef I2cHandle;

uint8_t TxBuffer[5] = "VICA";
uint8_t RxBuffer[5] = "NIST";

// slave address
//#define I2C_ADDRESS 0x50
#define I2C_ADDRESS 0x42
// register address
//#define REG_CHIP_ID 0x01

// neki definovi za i2c
// hal = hardware abstraction layer
// fja koja ukljucuje clock za port B
#define I2Cx_SDA_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

// sda je na pinu 7, na portu B
#define I2Cx_SDA_PIN GPIO_PIN_7
#define I2Cx_SDA_GPIO_PORT GPIOB
// alternativna fja za pin
#define I2Cx_SDA_AF GPIO_AF4_I2C1

// isto sve samo za scl
#define I2Cx_SCL_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_PIN GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SCL_AF GPIO_AF4_I2C1

// ukljucuje clock za i2c
#define I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()

// nesto, might delete later
#define I2Cx_FORCE_RESET() __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET() __HAL_RCC_I2C1_RELEASE_RESET()

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {

	// inicijalizacija i2c pinova
    GPIO_InitTypeDef GPIO_InitStruct;

    // pozivaju se za clock
    I2Cx_SCL_GPIO_CLK_ENABLE();
    I2Cx_SDA_GPIO_CLK_ENABLE();

    //s
    GPIO_InitStruct.Pin = I2Cx_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = I2Cx_SCL_AF;
    HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2Cx_SDA_PIN;
    GPIO_InitStruct.Alternate = I2Cx_SDA_AF;
    HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
    I2Cx_FORCE_RESET();
    I2Cx_RELEASE_RESET();
    HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
    HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);
}

/*
void i2cWrite(uint8_t* buf, uint8_t len, uint8_t addr) {

	HAL_I2C_Mem_Write(&I2cHandle, I2C_ADDRESS<<1, addr, I2C_MEMADD_SIZE_8BIT, buf, len, 10000);
}
*/

void initI2c() {

	//inicijalizujemo hal
	//HAL_Init();
	__HAL_RCC_I2C1_CLK_ENABLE();

	//GPIO_InitTypeDef GPIO_InitStructure;

	//koristimo i2cHandle strukturu
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
/*
    // fja za pisanje ka slejvu
    HAL_I2C_Mem_Write(&I2cHandle, I2C_ADDRESS<<1, REG_CHIP_ID, I2C_MEMADD_SIZE_8BIT, TxBuffer, 5, 10000);
    trace_puts("Written: ");
    for (int i=0; i<5; i++)
    {
    	trace_putchar(TxBuffer[i]);
    }
    trace_printf("\r\n");

    HAL_Delay(1000);

    // za citanje
    HAL_I2C_Mem_Read(&I2cHandle, I2C_ADDRESS<<1, REG_CHIP_ID, I2C_MEMADD_SIZE_8BIT, RxBuffer, 5, 10000);
    trace_puts("Read: ");
    for (int i=0; i<5; i++)
    {
    	trace_putchar(RxBuffer[i]);
    }
*/

    HAL_Delay(1000);
    //while(1);
}

void i2cApi_write(uint8_t* in, uint8_t len) {

//	HAL_I2C_Mem_Write(&I2cHandle, I2C_ADDRESS<<1, in[0], I2C_MEMADD_SIZE_8BIT, &in[1], len-1, 10000);
	HAL_I2C_Master_Transmit(&I2cHandle,I2C_ADDRESS<<1,in,len,10000);
}

void i2cApi_read(uint8_t* out, uint8_t len) {

//    HAL_I2C_Mem_Read(&I2cHandle, I2C_ADDRESS<<1, out[0], I2C_MEMADD_SIZE_8BIT, &out[0], len, 10000);
   HAL_I2C_Master_Receive(&I2cHandle,I2C_ADDRESS<<1,out,len,10000);
}
