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

void ModeHandler::registerMode(MODE id, ModeBase *mode){
	modeHandlers[static_cast<uint8_t>(id)] = mode;
}

void ModeHandler::setMode(MODE mode){
	if(modeHandlers[static_cast<uint8_t>(mode)] != nullptr){
		activeMode = mode;
	}
}

}
