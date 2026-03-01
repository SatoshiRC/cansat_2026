/*
 * ModeHandler.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEHANDLER_H_
#define INC_MODEHANDLER_H_

#include <array>

#include "ModeBase.h"
#include "Command/Inc/CommandManager.h"
#include "config.h"
#include "CAT24M01EEPROM.h"

namespace mode {

class ModeHandler {
	std::array<ModeBase*, static_cast<uint8_t>(MODE::Last)> modeHandlers;
	command::CommandManager *commandManager;
	MODE activeMode = MODE::WAKE_UP;
	Config *_config;
	CAT24M01_EEPROM *eeprom;
public:
	ModeHandler(command::CommandManager *commandManager, Config *config, CAT24M01_EEPROM *eeprom);
	void executeInloop();
	void onGpsUpdate(const NEDPosition &position);
	void onImuUpdate(const ImuOutput &imu);
	void onAltitudeUpdate(const float altitude);

	void registerMode(ModeBase *mode);
	void setMode(MODE mode);
	MODE getActiveMode(){
		return activeMode;
	}
};

}  // namespace mode

#endif /* INC_MODEHANDLER_H_ */
