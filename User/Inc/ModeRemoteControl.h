/*
 * ModeRemoteControl.h
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEREMOTECONTROL_H_
#define INC_MODEREMOTECONTROL_H_

#include <ModeBase.h>

#include "Parachute.h"
#include "ServoGripper.h"
#include "Drive.h"

class ModeRemoteControl: public ModeBase {
	Parachute *parachute;
	ServoGripper *stabilizer;
	Drive *drive;

public:
	ModeRemoteControl(Parachute *patachute, ServoGripper *stabilizer, Drive *drive);
	void execute();

	void enableParachute();
	void disableParachute();
	void setParachuteState(SERVO_STATE leftState, SERVO_STATE rightState);

	void enableStabilizer();
	void disableStabilizer();

	void enableDrive();
	void disableDrive();

};

#endif /* INC_MODEREMOTECONTROL_H_ */
