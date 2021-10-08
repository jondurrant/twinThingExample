/**
 * State for thing development test
 *
 * Jon Durrant - 19-Sep-2021
 */

#include "pico/stdlib.h"
#include "StateTemp.h"
#include "StateExample.h"
#include "ExampleObserver.h"
#include <stdio.h>
#include "hardware/uart.h"
#include <random>
#include "tiny-json.h"
#include "TopicGet.h"
#include "TopicPing.h"
#include "TwinUart.h"


#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 12
#define UART_RX_PIN 13

void uartSetup(){
	 // Set up our UART with the required speed.
	uart_init(UART_ID, BAUD_RATE);

	// Set the TX and RX pins by using the function select on the GPIO
	// Set datasheet for more information on function select
	gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

	uart_set_hw_flow(UART_ID, false, false);
	uart_set_fifo_enabled(UART_ID, true);

	uart_set_format(UART_ID,  8, 1, UART_PARITY_NONE );

}




int main() {
	char sbuf[20];

	//Initialise IO as we are using printf for debug
	stdio_init_all();

	uartSetup();


	//StateTemp state;
	StateExample state;
	ExampleObserver observ(&state);

	//Twin IO Mgt
	char readBuf[200];
	char writeBuf[200];
	char eventBuf[200];
	unsigned int bufLen=200;
	json_t jsonBuf[20];
	unsigned int jsonLen = 20;
	TwinUart twin(&state, readBuf, bufLen, writeBuf, bufLen, eventBuf, bufLen, jsonBuf, jsonLen);


	char buf[80];

	bool on = false;

	unsigned int u;

	int readChar;
	int readBufI = 0;

	u = state.state(buf, 80);
	if (u == 0){
		printf("{\"error\": true}\n");
	}else {
		printf("%s\n", buf);
	}

	unsigned int intTime = to_ms_since_boot(get_absolute_time ()) / 1000;

	 while (true) {
		unsigned int now = to_ms_since_boot(get_absolute_time ()) / 1000;
		if ((now - intTime) > 10){
			intTime = now;

			state.startTransaction();
			state.updateTemp();
			twin.publishMsg("temp", "new");

			unsigned char c = rand()%256;
			state.setRGB(c, c, c);
			state.commitTransaction();
		}
		twin.readTimeout(10);
	 }

}

