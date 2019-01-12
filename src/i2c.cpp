#include <stm32f4xx_hal.h>
#include "diag/Trace.h"
#include <stdint.h>

I2C_HandleTypeDef I2cHandle;

// slave address
#define I2C_ADDRESS 0x42

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

// TODO
#define I2Cx_FORCE_RESET() __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET() __HAL_RCC_I2C1_RELEASE_RESET()

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {

	// inicijalizacija i2c pinova
    GPIO_InitTypeDef GPIO_InitStruct;

    // pozivaju se za clock
    I2Cx_SCL_GPIO_CLK_ENABLE();
    I2Cx_SDA_GPIO_CLK_ENABLE();

    // podesavaju se parametri za scl pin i poziva se init
    GPIO_InitStruct.Pin = I2Cx_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = I2Cx_SCL_AF;
    HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

    // podesavauj se parametri za sda pin i init, ostali parametri ostaju isti
    GPIO_InitStruct.Pin = I2Cx_SDA_PIN;
    GPIO_InitStruct.Alternate = I2Cx_SDA_AF;
    HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
}

// f-ja za deinicijalizaciju i2c-a
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) {
    I2Cx_FORCE_RESET();
    I2Cx_RELEASE_RESET();
    HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
    HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);
}

void initI2c() {

	// poziva se HAL biblioteka za ukljcivanje clocka za i2c
	__HAL_RCC_I2C1_CLK_ENABLE();

	//GPIO_InitTypeDef GPIO_InitStructure;

	//koristi se i2cHandle struktura, postavljaju se parametri
	// TODO
	I2cHandle.Instance = I2C1; 									// koristimo I2C1 base adresu
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;	// koristimo sedmobitnu adresu
    I2cHandle.Init.ClockSpeed = 400000;						    // max brzina casovnika za gesture board
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;	// iskljuje se mod dualne adrese
    I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_16_9;				// koristimo fast mode duty cycle
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;	// ne koristimo general call mode
    I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;		// no stretch se iskljucuje
    I2cHandle.Init.OwnAddress1 = 0;								// adrese nam nisu potrebne
    I2cHandle.Init.OwnAddress2 = 0;								//

    // inicijalizuje i2c sa parametrima iz strukture
    if(HAL_I2C_Init(&I2cHandle) != HAL_OK) {
    	trace_puts("I2C init failed");
   	    while(1);
   	}

    trace_puts("I2C init passed");

    HAL_Delay(1000);
}

// Funkcije za pisanje i citanje podataka preko I2C-a
void i2cApi_write(uint8_t* in, uint8_t len) {

	// za stm slave adresa mora da se siftuje za 1
	HAL_I2C_Master_Transmit(&I2cHandle, I2C_ADDRESS<<1, in, len, 10000);
}

void i2cApi_read(uint8_t* out, uint8_t len) {

   HAL_I2C_Master_Receive(&I2cHandle, I2C_ADDRESS<<1, out, len, 10000);
}
