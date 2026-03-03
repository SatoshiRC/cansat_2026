/*
 * MotorUtil.h
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "tim.h"

class Motor {
	TIM_HandleTypeDef *htim;
	uint32_t channelA;
	uint32_t channelB;
	uint16_t maxCounter;
public:
	Motor(TIM_HandleTypeDef *htim = nullptr, uint32_t channelA = 0, uint32_t channelB = 0, uint16_t maxCounter = 0);
	void enable();
	void disable();

	void standby();
	void setVelocityInPercent(float velocity);
	void brake();

	int8_t getPower();
};

#endif /* INC_MOTOR_H_ */
