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

namespace mode{

enum class MODE{
	WAKE_UP,
	READY,
	DECENT,
	RELATIVE_NAVIGATION,
	ABSOLUTE_NAVIGATION,
	GOAL,
	REMOTE_CONTROL,
	AttitudeEstimationTest,
	Last,
};

class ModeBase {
	MODE mode;
protected:
	MODE nextMode;
public:
	ModeBase(MODE mode = MODE::Last);
	void initialize(){};
	void execute(){};
	void onGpsUpdate(const NEDPosition &position){};
	void onImuUpdate(){};
	void onAltitudeUpdate(const uint16_t altitude){};

	MODE getNextMode();
};

}

#endif /* INC_MODEBASE_H_ */
