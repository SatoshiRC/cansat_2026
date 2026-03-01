/*
 * ModeDecent.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeDecent.h>

namespace mode{

Decent::Decent(command::CommandManager *commandManager, Parachute *parachute, Drive *drive, ElapsedTimer *elapsedTimer)
:ModeBase(commandManager),
 parachute(parachute),
 drive(drive),
 elapsedTimer(elapsedTimer){

}

void Decent::initialize(){
	nextMode = mode;
}

void Decent::execute(){

}

void Decent::onAltitudeUpdate(const uint16_t altitude){
	if(altitude < parachuteReleaseAlt){
		parachute->release();

	}
}

}
