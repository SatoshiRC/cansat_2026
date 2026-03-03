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
#include "ICM20948_USER.h"
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
	Debug,
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
	virtual void initialize(){
		nextMode = MODE::Last;
	};
	virtual void finalize(){};
	virtual void execute(){};
	virtual void onGpsUpdate(const NEDPosition &position){};
	virtual void onImuUpdate(const ImuOutput &imu){};
	virtual void onAltitudeUpdate(const uint16_t altitude){};

	MODE getNextMode();
	virtual constexpr MODE getMode() = 0;
};

}

#endif /* INC_MODEBASE_H_ */
