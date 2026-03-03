/*
 * AbsoluteNavigation.cpp
 *
 *  Created on: Mar 1, 2026
 *      Author: OHYA Satoshi
 */

#include "AbsoluteNavigation.h"

namespace mode {

AbsoluteNavigation::AbsoluteNavigation(command::CommandManager *commandManager, ElapsedTimer *elapsedTimer, Drive *drive, const Config *config)
		:ModeBase(commandManager),
		 drive(drive),
		 config(config),
		 timer(elapsedTimer){
	// TODO Auto-generated constructor stub

}

void AbsoluteNavigation::initialize(){
	for(uint8_t n=0; n<3; n++){
		magnetGain[n] = 1/(config->magnetMax[n] - config->magnetOffset[n]);
	}
	sequenceTransitionTimeStamp = timer->getTimeMS();
	startTimeStamp = timer->getTimeMS();
	directionFromCamera = 0;
	isGoalDetectedByCamera = false;
	distanceMeasuredByTof = 0;
	isGoalDetectedByTof = false;
}

void AbsoluteNavigation::execute(){
	DriveVelocity velocity;
	float directionError = _targetHeadingDirection - _headingDirection;

	if(timer->getTimeMS() - startTimeStamp > 20*60*1000){
		sequence = Sequence::goal;
	}
	if(sequence == Sequence::absoluteNavigation){
		while(directionError > 2*std::numbers::pi){
			directionError -= 2*std::numbers::pi;
		}
		while(directionError < -2*std::numbers::pi){
			directionError += 2*std::numbers::pi;
		}
		float absError = std::abs(directionError);
		if(absError < 15*std::numbers::pi/180.0){
			velocity.angularVelocity = directionError/absError*baseSpeed/3.0;
		}else{
			velocity.angularVelocity = sin(directionError*180/15)*baseSpeed/2.0;
			velocity.velocity = baseSpeed;
		}
	}else if(sequence < Sequence::relativeNavigation){
		if(isGoalDetectedByCamera == true){
			sequence = Sequence::relativeNavigation;
			sequenceTransitionTimeStamp = timer->getTimeMS();
		}
		if(timer->getTimeMS() - sequenceTransitionTimeStamp > 10*1000){
			sequence = static_cast<Sequence>(static_cast<uint8_t>(sequence) + 1);
			sequenceTransitionTimeStamp = timer->getTimeMS();
			_targetHeadingDirection += 2*std::numbers::pi / 7;
			float absError = std::abs(directionError);
			if(absError < 15*std::numbers::pi/180.0){
				velocity.angularVelocity =
				velocity.velocity = std::abs(velocity.angularVelocity);
			}
		}
	}else if(sequence == Sequence::relativeNavigation){
		if(isGoalDetectedByCamera == false){
			sequence = Sequence::relativeNavigation_search0;
			sequenceTransitionTimeStamp = timer->getTimeMS();
		}
		if(isGoalDetectedByCamera == true){
			velocity.angularVelocity = -directionFromCamera*baseSpeed;
			velocity.velocity = baseSpeed;
		}
		if((isGoalDetectedByTof == true && distanceMeasuredByTof < 10) ||
				timer->getTimeMS() - sequenceTransitionTimeStamp > 300*1000){
			sequence = Sequence::goal;
		}
	}
	drive->drive(velocity);
}


void AbsoluteNavigation::onGpsUpdate(const NEDPosition &position){
	distance = std::hypot(-position.east, position.north);
	if(distance < relativeNavigationStartTh && sequence == Sequence::absoluteNavigation){
		sequence = Sequence::relativeNavigation_search0;
		sequenceTransitionTimeStamp = timer->getTimeMS();
		_targetHeadingDirection = std::atan2(-position.east, position.north);
	}else if(distance > absoluteNavigationStartTh && sequence > Sequence::absoluteNavigation){
		sequence = Sequence::absoluteNavigation;
		sequenceTransitionTimeStamp = timer->getTimeMS();
		_targetHeadingDirection = std::atan2(-position.east, position.north);
	}
	auto data = static_cast<command::AbsoluteNavigation*>((*commandManager)[command::COMMAND_ID::AbsoluteNavigationLog])->getData();
	data.relativePositionNorth() = position.north;
	data.relativePositionEast() = position.east;

	commandManager->transmit(command::COMMAND_ID::AbsoluteNavigationLog);
}

void AbsoluteNavigation::onImuUpdate(const ImuOutput &imu){
	_headingDirection = std::atan2((imu.m[0] - config->magnetOffset[0])*magnetGain[0], -(imu.m[1] - config->magnetOffset[1])*magnetGain[1]);
}

} /* namespace mode */
