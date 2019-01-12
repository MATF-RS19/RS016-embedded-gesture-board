/*
 * cUart.h
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#ifndef CUART_H_
#define CUART_H_

#include <stm32f4xx_hal.h>
#include "diag/Trace.h"

class cUart {
public:
	cUart();
	virtual ~cUart();

	void init();
	void send(uint8_t *buff, uint8_t size);

private:
	UART_HandleTypeDef s_UARTHandle;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef * txPort;
	uint32_t txPin;
	GPIO_TypeDef * rxPort;
	uint32_t rxPin;
};

#endif /* CUART_H_ */
