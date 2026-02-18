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

namespace mode {

class ModeHandler {
	std::array<ModeBase*, static_cast<uint8_t>(MODE::Last)> modeHandlers;
	command::CommandManager *commandManager;
	MODE activeMode;
public:
	ModeHandler() = default;
	ModeHandler(command::CommandManager *commandManager);
	void executeInloop();
	void onGpsUpdate(const NEDPosition &position);
	void onImuUpdate();
	void onAltitudeUpdate(const float altitude);

	void registerMode(ModeBase *mode);
	void setMode(MODE mode);
	MODE getActiveMode(){
		return activeMode;
	}
};

}  // namespace mode

#endif /* INC_MODEHANDLER_H_ */
