/*
 * ModeWakeUp.cpp
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeWakeUp.h>

namespace mode{

void WakeUp::initialize(){
	nextMode = mode;
}

void WakeUp::execute(){
	if(nmeaProcessor->isReferenceSet() == false){
		return;
	}
	if(nmeaProcessor->getLastPoint().valid == 0){
		return;
	}
	if(altitudeEstimation->isCompleteCalibration() == false){
		return;
	}

	nextMode = MODE::READY;
}

void WakeUp::onGpsUpdate(const NEDPosition &position){
	commandManager->transmit(command::COMMAND_ID::GPS);
}

}
