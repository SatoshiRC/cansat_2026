/*
 * ServoGripper.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <ServoGripper.h>

ServoGripper::ServoGripper(ActuatorState *state, TIM_HandleTypeDef *htim, uint32_t channel, ServoGripperConfig* config)
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
	_config->releaseCount = count;
	release();
}

void ServoGripper::setGripCount(int16_t count){
	_config->gripCount = count;
	grip();
}

void ServoGripper::setCenterCount(int16_t count){
	_config->centerCount = count;
	center();
}

uint16_t ServoGripper::getReleaseCount(){
	return _config->releaseCount;
}
uint16_t ServoGripper::getGripCount(){
	return _config->gripCount;
}
uint16_t ServoGripper::getCenterCount(){
	return _config->centerCount;
}

void ServoGripper::release(){
	servoState = SERVO_STATE::RELEASE;
	__HAL_TIM_SET_COMPARE(htim, channel, _config->releaseCount);
}
void ServoGripper::grip(){
	servoState = SERVO_STATE::GRIP;
	__HAL_TIM_SET_COMPARE(htim, channel, _config->gripCount);
}

void ServoGripper::center(){
	servoState = SERVO_STATE::CENTER;
	__HAL_TIM_SET_COMPARE(htim, channel, _config->centerCount);
}

void ServoGripper::setServoState(SERVO_STATE state){
	servoState = state;
	if(state == SERVO_STATE::CENTER){
		center();
	}else if(state == SERVO_STATE::RELEASE){
		release();
	}else if(state == SERVO_STATE::GRIP){
		grip();
	}
}
