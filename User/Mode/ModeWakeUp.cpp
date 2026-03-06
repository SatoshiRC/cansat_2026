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
	commandManager->transmit(command::COMMAND_ID::ServoConfig_prachuteLeft);
	HAL_Delay(10);
	commandManager->transmit(command::COMMAND_ID::ServoConfig_prachuteRight);
	HAL_Delay(10);
	commandManager->transmit(command::COMMAND_ID::ServoConfig_stabilizer);
	HAL_Delay(10);
	commandManager->transmit(command::COMMAND_ID::Goal);
	HAL_Delay(10);
	commandManager->transmit(command::COMMAND_ID::Mode);
	HAL_Delay(10);
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

	if(_resumeFrom != MODE::Last){
		nextMode = _resumeFrom;
		_resumeFrom = MODE::Last;
	}else{
		nextMode = MODE::READY;
	}
}

void WakeUp::onGpsUpdate(const NEDPosition &position){

}

void WakeUp::resumeFrom(MODE from){
	_resumeFrom = from;
}
}
