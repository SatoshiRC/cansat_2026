/*
 * ModeGoal.cpp
 *
 *  Created on: Mar 6, 2026
 *      Author: satoshi
 */

#include <ModeGoal.h>

namespace mode{
ModeGoal::ModeGoal(command::CommandManager *commandManager, Drive *drive)
		:ModeBase(commandManager),
		 drive(drive){
	// TODO Auto-generated constructor stub

}

void ModeGoal::initialize(){
	drive->brake();
}

void ModeGoal::execute(){
	drive->brake();
}

void ModeGoal::onAltitudeUpdate(const uint16_t altitude){
	commandManager->transmit(command::COMMAND_ID::Mode);
}
}
