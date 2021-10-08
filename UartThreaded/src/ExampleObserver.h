/*
 * ExampleObserver.h
 *
 *  Example Observer takes a state from a StateExample object
 *  Looks for the state of On state variable and sets the onboard LED to
 *  be on or off
 *
 *  Created on: 21 Sept 2021
 *      Author: jondurrant
 */

#ifndef EXAMPLEOBSERVER_H_
#define EXAMPLEOBSERVER_H_

#include "StateObserver.h"
#include "State.h"
#include "StateExample.h"

/***
 * Example Observer which prints the delta on notification
 */
class ExampleObserver : public StateObserver {
public:
	/***
	 * Constructor - Attaches to State and initialises the LED
	 * @param s - State object to attach to
	 */
	ExampleObserver(StateExample* s);

	/***
	 * Destructor
	 */
	virtual ~ExampleObserver();

	/***
	 * Notify called by State object to notify of a change.
	 * @param dirtyCode - used for pulling back delta of only notified change
	 */
	virtual void notifyState(unsigned char dirtyCode);
private:
	StateExample* state = NULL;
};

#endif /* EXAMPLEOBSERVER_H_ */
