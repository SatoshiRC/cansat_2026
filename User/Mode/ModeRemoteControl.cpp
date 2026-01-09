/*
 * ModeRemoteControl.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeRemoteControl.h>

namespace mode{

RemoteControl::RemoteControl(Parachute *patachute, ServoGripper *stabilizer, Drive *drive, ElapsedTimer *timer)
:parachute(parachute), stabilizer(stabilizer), drive(drive), timer(timer) ,ModeBase( MODE::REMOTE_CONTROL){
	// TODO Auto-generated constructor stub

}

void RemoteControl::initialize(){

}

void RemoteControl::execute(){

}

}
