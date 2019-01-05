/*
 * cUart.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#include "cUart.h"

cUart::cUart() {
	// TODO Auto-generated constructor stub

}

cUart::~cUart() {
	// TODO Auto-generated destructor stub
}

void cUart::init()
{
	s_UARTHandle = UART_HandleTypeDef();

	//HAL_Init();
	__USART2_CLK_ENABLE();
	//__GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	s_UARTHandle.Instance        = USART2;
	s_UARTHandle.Init.BaudRate   = 115200;
	s_UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
	s_UARTHandle.Init.StopBits   = UART_STOPBITS_1;
	s_UARTHandle.Init.Parity     = UART_PARITY_NONE;
	s_UARTHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	s_UARTHandle.Init.Mode       = UART_MODE_TX_RX;

	if (HAL_UART_Init(&s_UARTHandle) != HAL_OK) {
		trace_puts("UArt init failed");
	    while(1);
	}

	trace_puts("Uart init passed");

	uint8_t buffer[] = "Uart init";
	HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}

void cUart::send(uint8_t *buff, uint8_t size)
{
	for(uint8_t i = 0; i<size; i++)
		HAL_UART_Transmit(&s_UARTHandle, buff+i, 1, HAL_MAX_DELAY);
}
