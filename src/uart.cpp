#include <stm32f4xx_hal.h>
#include <string.h>
#include "diag/Trace.h"

static UART_HandleTypeDef s_UARTHandle;

void uartSendGestureData(uint8_t dat)
{
    switch (dat)
    {
      case 1:
        trace_printf("GARBAGE\r\n");  // Unprocessed gestures are defined as "garbage"
        break;
      case 2:
        trace_printf("flick left to right\r\n");
        break;
      case 3:
       trace_printf("flick right to left\r\n");
        break;
      case 4:
        trace_printf("flick up\r\n");
        break;
      case 5:
        trace_printf("flick down\r\n");
        break;
      case 6:
        trace_printf("Tap north\r\n");
        break;
      case 7:
       trace_printf("Tap south\r\n");
        break;
      case 8:
        trace_printf("Tap east\r\n");
        break;
      case 9:
        trace_printf("Tap west\r\n");
        break;
      case 10:
        trace_printf("Double Tap north\r\n");
        break;
      case 11:
       trace_printf("Double Tap south\r\n");
        break;
      case 12:
        trace_printf("Double Tap east\r\n");
        break;
      case 13:
        trace_printf("Double Tap west\r\n");
        break;
      case 14:
        trace_printf("Tap center\r\n");
        break;
      case 15:
        trace_printf("Double Tap center\r\n");
        break;
      case 16:
        trace_printf("Clockwise\r\n");
        break;
      case 17:
        trace_printf("Counter Clockwise\r\n");
        break;
    }

    HAL_UART_Transmit(&s_UARTHandle, &dat, 1, HAL_MAX_DELAY);
}

void initUart() {
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

	uint8_t buffer[] = "init";
	HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);

}
