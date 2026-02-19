/*
 * ModeRemoteControl.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeRemoteControl.h>

namespace mode{

RemoteControl::RemoteControl(command::CommandManager *commandManager, Parachute *parachute, ServoGripper *stabilizer, Drive *drive, ElapsedTimer *timer)
:ModeBase(commandManager),parachute(parachute), stabilizer(stabilizer), drive(drive), timer(timer){
	// TODO Auto-generated constructor stub

}

void RemoteControl::initialize(){
	nextMode = mode;
}

void RemoteControl::execute(){

}

}
