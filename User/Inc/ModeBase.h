/*
 * StateBase.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEBASE_H_
#define INC_MODEBASE_H_

#include "State.h"
#include "GPS.h"

enum class MODE{
	Invalid,
	WAKE_UP,
	READY,
	DECENT,
	LANDING,
	RELATIVE_NAVIGATION,
	ABSOLUTE_NAVIGATION,
	GOAL,
	REMOTE_CONTROL,
};

class ModeBase {
	const MODE mode;
	MODE nextMode;
public:
	ModeBase(MODE mode = MODE::Invalid);
	virtual MODE execution() = 0;
	void onGpsUpdate(const NEDPosition &position){};
	void onImuUpdate(){};
	void onAltitudeUpdate(const uint16_t altitude){};
};

#endif /* INC_MODEBASE_H_ */
