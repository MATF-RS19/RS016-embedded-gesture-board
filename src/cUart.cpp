/*
 * cUart.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Ana
 */

#include "cUart.h"

cUart::cUart() {

	txPin = GPIO_PIN_5;
	rxPin = GPIO_PIN_6;
	txPort = GPIOD;
	rxPort = GPIOD;

	// postavljaju se parametri na uart handle
	s_UARTHandle.Instance        = USART2;				// base address
	s_UARTHandle.Init.BaudRate   = 115200;				// broj bitova po sekundi
	s_UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;	// salje se 1 bajt
	s_UARTHandle.Init.StopBits   = UART_STOPBITS_1;		// korisitmo 1 stop bit
	s_UARTHandle.Init.Parity     = UART_PARITY_NONE;    // ne koristimo parity bit
	s_UARTHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;	// ne koristimo hw flow control
	s_UARTHandle.Init.Mode       = UART_MODE_TX_RX;		// mod je tx_rx - transmit i recieve

}

cUart::~cUart() {

}

//  prebaciti u konstruktor

void cUart::init() {
	__USART2_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure;

	// port D, pin 6 je za rx - recieve
	GPIO_InitStructure.Pin = rxPin;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(rxPort, &GPIO_InitStructure);

	// port D, pin 5 je za tx - transmit
	GPIO_InitStructure.Pin = txPin;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
	HAL_GPIO_Init(txPort, &GPIO_InitStructure);

	if (HAL_UART_Init(&s_UARTHandle) != HAL_OK) {
		trace_puts("Uart init failed");
	    while(1);
	}

	trace_puts("Uart init passed");

	// provera
	// uint8_t buffer[] = "init";
	// HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
}


// pozivao HAL fukciu za slaje preko uart-a
// buff - buffer bajtova koji se salje
// size - broj bajtova koe saljeo
void cUart::send(uint8_t *buff, uint8_t size)
{
		HAL_UART_Transmit(&s_UARTHandle, buff, size, HAL_MAX_DELAY);
}
