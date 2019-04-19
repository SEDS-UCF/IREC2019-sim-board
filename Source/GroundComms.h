#ifndef IREC2019_SIM_BOARD_GROUNDCOMMS_H
#define IREC2019_SIM_BOARD_GROUNDCOMMS_H

#include "Auxiliary/circular_buffer.h"

#include <usart.h>

#include <stdint.h>

#define GND_UART huart3
#define GND_BUF_SIZE 1024

extern volatile uint8_t rx_byte;
extern volatile cbuf_handle_t rx_buf;
extern volatile bool gnd_eol;

void init_ground_comms();
void handle_ground_comms();

#endif //IREC2019_SIM_BOARD_GROUNDCOMMS_H
