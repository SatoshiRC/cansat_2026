/*
 * ModeReady.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeReady.h>

namespace mode{

Ready::Ready(command::CommandManager *commandManager)
:ModeBase(commandManager)
{
	// TODO Auto-generated constructor stub

}

void Ready::initialize(){
	nextMode = mode;
}

void Ready::execute(){

}

void Ready::onAltitudeUpdate(const float altitude){
	if(altitude > 10*1000){
		nextMode = MODE::DECENT;
	}
}

}
