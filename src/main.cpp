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
#include <random>
#include "tiny-json.h"
#include "TwinStdio.h"
#include "TopicGet.h"
#include "TopicPing.h"




int main() {
	char sbuf[20];

	//Initialise IO as we are using printf for debug
	stdio_init_all();


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
	TwinStdio twin(&state, readBuf, bufLen, writeBuf, bufLen, eventBuf, bufLen, jsonBuf, jsonLen);


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

	 while (true) {
		 for (int i=0; i < 5; i++){
			state.startTransaction();
			state.updateTemp();
			twin.publishMsg("temp", "new");


			if (i == 3){
				unsigned char c = rand()%256;
				state.setRGB(c, c, c);
			}
			state.commitTransaction();

			twin.readTimeout(0);

			sleep_ms(1000);
		 }
	 }

}

