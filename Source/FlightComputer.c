#include "FlightComputer.h"

#include "Auxiliary/Printing.h"
#include "GroundComms.h"

#include <gpio.h>
#include <usart.h>

void FC_Setup() {
	HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);

	init_ground_comms();

	dbg_println("Setup reached.");

//	dbg_print("Sending test msgpack to Pi... ");
//	char test[] = {0x93, 0x01, 0x07, 0x95, 0x01, 0x02, 0x03, 0x04, 0x05};
//	HAL_UART_Transmit(&huart3, test, sizeof(test), 1000);
//	dbg_println("Done!");
}

void FC_Tick() {
	if(gnd_eol)
		handle_ground_comms();
}