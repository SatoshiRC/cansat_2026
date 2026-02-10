/*
 * ModeHandler.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeHandler.h>

namespace mode{

ModeHandler::ModeHandler() {
	// TODO Auto-generated constructor stub

}

void ModeHandler::executeInloop(){
	modeHandlers[static_cast<uint8_t>(activeMode)]->execute();
}

void ModeHandler::onGpsUpdate(const NEDPosition &position){
	modeHandlers[static_cast<uint8_t>(activeMode)]->onGpsUpdate(position);
};
void ModeHandler::onImuUpdate(){
	modeHandlers[static_cast<uint8_t>(activeMode)]->onImuUpdate();
};
void ModeHandler::onAltitudeUpdate(const float altitude){
	modeHandlers[static_cast<uint8_t>(activeMode)]->onAltitudeUpdate(altitude);
}

void ModeHandler::registerMode(ModeBase *mode){
	modeHandlers[static_cast<uint8_t>(mode->getMode())] = mode;
}

void ModeHandler::setMode(MODE mode){
	if(modeHandlers[static_cast<uint8_t>(mode)] != nullptr){
		activeMode = mode;
	}
}

}
