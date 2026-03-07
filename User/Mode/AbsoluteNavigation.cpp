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
	while(directionError > std::numbers::pi){
		directionError -= 2*std::numbers::pi;
	}
	while(directionError < -std::numbers::pi){
		directionError += 2*std::numbers::pi;
	}

	if(timer->getTimeMS() - startTimeStamp > 10*60*1000){
		sequence = Sequence::goal;
	}
	if(sequence == Sequence::absoluteNavigation){
		float absError = std::abs(directionError);
		if(absError > 15*std::numbers::pi/180.0){
			velocity.angularVelocity = directionError/absError*baseSpeed*1.2;
		}else{
			velocity.angularVelocity = sin(directionError*180/15)*baseSpeed*0.6;
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
			while(_targetHeadingDirection > std::numbers::pi){
				_targetHeadingDirection -= 2*std::numbers::pi;
			}
		}
		float absError = std::abs(directionError);
		velocity.angularVelocity = directionError*50;

	}else if(sequence == Sequence::relativeNavigation){
		if(isGoalDetectedByCamera == false){
			sequence = Sequence::relativeNavigation_search0;
			sequenceTransitionTimeStamp = timer->getTimeMS();
		}
		if(isGoalDetectedByCamera == true){
			_targetHeadingDirection =  _headingDirection + directionFromCamera;
			velocity.angularVelocity = -directionFromCamera*baseSpeed*2;
			velocity.velocity = baseSpeed;
			if((distanceMeasuredByTof < 30) ||
				timer->getTimeMS() - sequenceTransitionTimeStamp > 60*1000){
				sequence = Sequence::goal;
			}
		}
	}

	drive->drive(velocity);

	if(sequence == Sequence::goal){
		nextMode = MODE::GOAL;
	}
}


void AbsoluteNavigation::onGpsUpdate(const NEDPosition &position){
	distance = std::hypot(-position.east, position.north);
	if(distance < relativeNavigationStartTh && sequence == Sequence::absoluteNavigation){
		sequence = Sequence::relativeNavigation_search0;
		sequenceTransitionTimeStamp = timer->getTimeMS();
		_targetHeadingDirection = std::atan2(position.east, -position.north);
	}else if(distance > absoluteNavigationStartTh && sequence > Sequence::absoluteNavigation){
		sequence = Sequence::absoluteNavigation;
		sequenceTransitionTimeStamp = timer->getTimeMS();
		_targetHeadingDirection = std::atan2(position.east, -position.north);
	}
	if(sequence == Sequence::absoluteNavigation){
		_targetHeadingDirection = std::atan2(position.east, -position.north);
	}
	auto data = static_cast<command::RelativeNavigation*>((*commandManager)[command::COMMAND_ID::RelativeNavigationLog])->getData();
	data.relativePositionNorth() = position.north;
	data.relativePositionEast() = position.east;
	data.headingDirection() = _headingDirection*180.0/std::numbers::pi;
	data.goalDirection() = _targetHeadingDirection*180.0/std::numbers::pi;
	data.isDetectedGoalOnCamera() = isGoalDetectedByCamera;
	data.tofDistance() = distanceMeasuredByTof;
	static_cast<command::RelativeNavigation*>((*commandManager)[command::COMMAND_ID::RelativeNavigationLog])->setData(data);

	commandManager->transmit(command::COMMAND_ID::RelativeNavigationLog);
}

void AbsoluteNavigation::onImuUpdate(const ImuOutput &imu){
	_headingDirection = std::atan2((imu.m[0] - config->magnetOffset[0])*magnetGain[0], -(imu.m[1] - config->magnetOffset[1])*magnetGain[1]);
}

} /* namespace mode */
