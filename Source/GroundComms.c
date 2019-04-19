#include "GroundComms.h"

#include "Auxiliary/Printing.h"

#include <mpack/mpack.h>

#define MAX_ARGS 15

volatile uint8_t rx_byte;
volatile cbuf_handle_t rx_buf;
volatile uint8_t rx_container[GND_BUF_SIZE] = {0};
volatile bool gnd_eol = false;

uint8_t yam_unpacker[GND_BUF_SIZE] = {0};

void init_ground_comms() {
	rx_buf = circular_buf_init((uint8_t*)rx_container, GND_BUF_SIZE);

	HAL_UART_Receive_IT(&GND_UART, (uint8_t*)&rx_byte, 1);
}

size_t read_bytes(mpack_tree_t* tree, char* buffer, size_t count) {
	if(circular_buf_empty(rx_buf))
		return 0;

	size_t cnt = 0;
	while(cnt + 1 < count && circular_buf_get(rx_buf, (uint8_t*)buffer + cnt++) == 0);

	return cnt;
}

void handle_ground_comms() {
	gnd_eol = false;

	mpack_reader_t reader;
	mpack_reader_init(&reader, yam_unpacker, GND_BUF_SIZE, 0);
	mpack_reader_set_fill(&reader, &read_bytes);

	mpack_expect_array_match(&reader, 3);

	uint8_t dest = mpack_expect_u8(&reader);
	uint16_t cmd = mpack_expect_u16(&reader);

	int args[MAX_ARGS];
	size_t arg_cnt = mpack_expect_array_max(&reader, MAX_ARGS);
	for(size_t i = 0; i < arg_cnt; ++i) {
		args[i] = mpack_expect_u64(&reader);
	}

	mpack_done_array(&reader);
	mpack_done_array(&reader);

	mpack_error_t error = mpack_reader_destroy(&reader);
	if (error != mpack_ok) {
		dbg_println("Error %i occurred reading data!\n", (int) error);
		return;
	}

	dbg_print("Got a good yam! DEST = %d, CMD = %d, ARG_CNT = %d, ARGS = [ ", dest, cmd, arg_cnt);
	for(size_t i = 0; i < arg_cnt; ++i)
		dbg_print("%d, ", args[i]);
	dbg_println("]");
}