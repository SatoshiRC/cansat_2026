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
