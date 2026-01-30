/*
 * ServoGripper.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <ServoGripper.h>

ServoGripper::ServoGripper(ActuatorState *state, TIM_HandleTypeDef *htim, uint32_t channel, ServoGripperConfig config)
:state(state), htim(htim), channel(channel),_config(config){};

void ServoGripper::enable(){
	*state = ACTUATOR_STATE::Active;
	HAL_TIM_PWM_Start(htim, channel);
}

void ServoGripper::disable(){
	*state = ACTUATOR_STATE::Disabled;
	HAL_TIM_PWM_Stop(htim, channel);
}

void ServoGripper::setReleaseCount(uint16_t count){
	_config.releaseCount = count;
	release();
}

void ServoGripper::setGripCount(int16_t count){
	_config.gripCount = count;
	grip();
}

uint16_t ServoGripper::getReleaseCount(){
	return _config.releaseCount;
}
uint16_t ServoGripper::getGripCount(){
	return _config.gripCount;
}

void ServoGripper::release(){
	*state = ACTUATOR_STATE::Active;
	__HAL_TIM_SET_COMPARE(htim, channel, _config.releaseCount);
}
void ServoGripper::grip(){
	*state = ACTUATOR_STATE::Active;
	__HAL_TIM_SET_COMPARE(htim, channel, _config.gripCount);
}

void ServoGripper::center(){
	*state = ACTUATOR_STATE::Active;
	__HAL_TIM_SET_COMPARE(htim, channel, _config.centerCount);
}

void ServoGripper::setServoState(SERVO_STATE state){
	if(state == SERVO_STATE::CENTER){
		center();
	}else if(state == SERVO_STATE::RELEASE){
		release();
	}else if(state == SERVO_STATE::GRIP){
		grip();
	}
}
