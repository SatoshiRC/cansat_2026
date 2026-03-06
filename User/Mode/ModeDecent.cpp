/*
 * ModeDecent.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeDecent.h>

namespace mode{

Decent::Decent(command::CommandManager *commandManager, Parachute *parachute, Drive *drive, ServoGripper *stabilizer, ElapsedTimer *elapsedTimer)
:ModeBase(commandManager),
 parachute(parachute),
 drive(drive),
 stabilizer(stabilizer),
 elapsedTimer(elapsedTimer){

}

void Decent::initialize(){
	nextMode = mode;
	timeStamp = 0;
	sequence = Sequence::Decent;
	commandData = CommandDataType::DecentLog();
	drive->brake();
	parachute->grip();
	stabilizer->grip();
}

void Decent::execute(){
	if(sequence == Sequence::ParachuteRelease && timeStamp + sequenceDelay[static_cast<uint8_t>(sequence)] < elapsedTimer->getTimeMS()){
		sequence = Sequence::StabilizerDeploy;
		stabilizer->release();
		DriveVelocity velo;
		velo.velocity = 40;
		velo.angularVelocity = 0;
		drive->drive(velo);
		commandData.isStabilizerDeploied = true;
		timeStamp = elapsedTimer->getTimeMS();
	}else if(sequence == Sequence::StabilizerDeploy && timeStamp + sequenceDelay[static_cast<uint8_t>(sequence)] < elapsedTimer->getTimeMS()){
		nextMode = MODE::ABSOLUTE_NAVIGATION;

	}
}

void Decent::onAltitudeUpdate(const uint16_t altitude){
	commandData.altitude = altitude;
	if(altitude < parachuteReleaseAlt ){
		parachute->release();
		commandData.isParachuteReleased = true;
		if(timeStamp == 0){
			timeStamp = elapsedTimer->getTimeMS();
			sequence = Sequence::ParachuteRelease;
		}
	}
	commandManager->transmit(command::COMMAND_ID::DecentLog);
}

}
