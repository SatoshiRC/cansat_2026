/*
 * ServoGripper.h
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_SERVOGRIPPER_H_
#define INC_SERVOGRIPPER_H_

#include "tim.h"
#include "State.h"
#include "config.h"

enum class SERVO_STATE{
	CENTER = 0,
	RELEASE,
	GRIP
};

class ServoGripper {
	ActuatorState *state;
	SERVO_STATE servoState;

	TIM_HandleTypeDef *htim;
	uint32_t channel;

	ServoGripperConfig *_config;
public:
	ServoGripper(ActuatorState *state = nullptr, TIM_HandleTypeDef *htim = nullptr, uint32_t channel = 0, ServoGripperConfig *config = new ServoGripperConfig());

	//configuration functions
	void setReleaseCount(uint16_t count);
	void setGripCount(int16_t count);
	void setCenterCount(int16_t count);
	uint16_t getReleaseCount();
	uint16_t getGripCount();
	uint16_t getCenterCount();
	ServoGripperConfig* config(){
		return _config;
	}
	SERVO_STATE getServoState(){
		return servoState;
	}


	//enable / disable PWM signal
	void enable();
	void disable();

	//actuation function
	void release();
	void grip();
	void center();
	void setServoState(SERVO_STATE state);
};

#endif /* INC_SERVOGRIPPER_H_ */
