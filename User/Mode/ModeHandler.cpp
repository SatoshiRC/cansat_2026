/*
 * ModeHandler.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeHandler.h>

namespace mode{

ModeHandler::ModeHandler(command::CommandManager *commandManager, Config *config, CAT24M01_EEPROM *eeprom)
		:commandManager(commandManager),
		 _config(config),
		 eeprom(eeprom){
	// TODO Auto-generated constructor stub

}

void ModeHandler::executeInloop(){
	modeHandlers[static_cast<uint8_t>(activeMode)]->execute();
}

void ModeHandler::onGpsUpdate(const NEDPosition &position){
	modeHandlers[static_cast<uint8_t>(activeMode)]->onGpsUpdate(position);
};
void ModeHandler::onImuUpdate(const ImuOutput &imu){
	modeHandlers[static_cast<uint8_t>(activeMode)]->onImuUpdate(imu);
};
void ModeHandler::onAltitudeUpdate(const float altitude){
	modeHandlers[static_cast<uint8_t>(activeMode)]->onAltitudeUpdate(altitude);
}

void ModeHandler::registerMode(ModeBase *mode){
	modeHandlers[static_cast<uint8_t>(mode->getMode())] = mode;
}

void ModeHandler::setMode(MODE mode){
	if(mode == activeMode){
		//When the given mode and current mode are same, don't do anything.
		return;
	}

	if(modeHandlers[static_cast<uint8_t>(mode)] != nullptr){
		modeHandlers[static_cast<uint8_t>(activeMode)]->finalize();
		activeMode = mode;
		eeprom->write();
		modeHandlers[static_cast<uint8_t>(activeMode)]->initialize();
	}
	commandManager->transmit(command::COMMAND_ID::Mode);
}

}
