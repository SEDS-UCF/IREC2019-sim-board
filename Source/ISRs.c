#include <usart.h>

#include "GroundComms.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &GND_UART) {
		if(!circular_buf_full(rx_buf))
			circular_buf_put2(rx_buf, rx_byte);

		HAL_UART_Receive_IT(&GND_UART, (uint8_t*)&rx_byte, 1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == GPIO_PIN_13)
		gnd_eol = true;
}