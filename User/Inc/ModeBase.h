/*
 * StateBase.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEBASE_H_
#define INC_MODEBASE_H_

#include "State.h"

enum class MODE{
	IDLE,
	READY,
	DECENT,
	LAND,
	RELATIVE_NAVIGATION,
	ABSOLUTE_NAVIGATION,
	GOAL
};

class ModeBase {
	MODE mode;
	State *state;
public:
	ModeBase(State *state = new State, MODE mode);
	virtual void execution() = 0;


};

#endif /* INC_MODEBASE_H_ */
