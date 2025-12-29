/*
 * ModeRemoteControl.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeRemoteControl.h>

ModeRemoteControl::ModeRemoteControl(Parachute *patachute, ServoGripper *stabilizer, Drive *drive)
:parachute(parachute), stabilizer(stabilizer), drive(drive), ModeBase( MODE::REMOTE_CONTROL){
	// TODO Auto-generated constructor stub

}

