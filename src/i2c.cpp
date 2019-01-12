#include <stm32f4xx_hal.h>
#include "diag/Trace.h"
#include <stdint.h>
#include "i2c.h"

I2C_HandleTypeDef I2cHandle;  // adle za i2c koi koristi HAL biblioteka za i2c

// handler funkcia koja se poziva u HHHHAl biblioteci kad pozovemo HAL_I2c_init
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {

	// inicijalizacija i2c pinova
    GPIO_InitTypeDef GPIO_InitStruct;

    // ukljucujemo clock za port B
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // scl pin nam je PORTB pin 6, pull up ukljucen (scl pin ce biti 1)
    // speed - fast, alternativna funkcija - i2c1
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // podesavauj se parametri za sda pin(PB7) i init, ostali parametri ostaju isti
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// handler f-ja za deinicijalizaciju i2c-a, poziva se u HAL kada hocemo da deinit i2c
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) {
	__HAL_RCC_I2C1_FORCE_RESET();  // resetuj i2c1 - HAL-ova funkcija
	__HAL_RCC_I2C1_RELEASE_RESET();
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);  // deinicijalizuj pinove pB6 i pB7
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);
}


// nasa funkcija za inicijalizaciju i2c-a, oslanja se na HAL
void initI2c() {

	// poziva se HAL biblioteka za ukljcivanje clocka za i2c
	__HAL_RCC_I2C1_CLK_ENABLE();

	//GPIO_InitTypeDef GPIO_InitStructure;

	//koristi se i2cHandle struktura, postavljaju se parametri
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
