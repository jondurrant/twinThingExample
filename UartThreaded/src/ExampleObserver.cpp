/*
 * ExampleObserver.cpp
 *
 * Example Observer takes a state from a StateExample object
 *  Looks for the state of On state variable and sets the onboard LED to
 *  be on or off
 *
 *  Created on: 21 Sept 2021
 *      Author: jondurrant
 */

#include "ExampleObserver.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "StateExample.h"


/***
* Constructor - Attaches to State and initialises the LED
* @param s - State object to attach to
*/
ExampleObserver::ExampleObserver(StateExample* s) {

	state = s;
	state->attach(this);

	const uint LED_PIN = PICO_DEFAULT_LED_PIN;

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
}

/***
 * Destructor
 */
ExampleObserver::~ExampleObserver() {
	// NOP
}

/***
* Notify called by State object to notify of a change.
* @param dirtyCode - used for pulling back delta of only notified change
*/
void ExampleObserver::notifyState(unsigned char dirtyCode){
	const uint LED_PIN = PICO_DEFAULT_LED_PIN;
	if (state->getOn()){
		gpio_put(LED_PIN, 1);
	} else {
		gpio_put(LED_PIN, 0);
	}

}

