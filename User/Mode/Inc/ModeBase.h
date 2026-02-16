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
//#include "CommandManager.h"
#include "Command/Inc/CommandManager.h"

namespace mode{

enum class MODE{
	WAKE_UP,
	READY,
	DECENT,
	LANDING,
	RELATIVE_NAVIGATION,
	ABSOLUTE_NAVIGATION,
	GOAL,
	REMOTE_CONTROL,
	AltitudeEstimationTest,
	Last,
};

class ModeBase {
	static constexpr MODE mode = MODE::Last;
protected:
	MODE nextMode;
	command::CommandManager *commandManager;

public:
	ModeBase():nextMode(mode){};
	ModeBase(command::CommandManager *commandManager):nextMode(mode),commandManager(commandManager){};
	void initialize(){};
	void execute(){};
	void onGpsUpdate(const NEDPosition &position){};
	void onImuUpdate(){};
	void onAltitudeUpdate(const uint16_t altitude){};

	MODE getNextMode();
	constexpr MODE getMode(){
		return mode;
	}
};

}

#endif /* INC_MODEBASE_H_ */
