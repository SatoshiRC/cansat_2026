/*
 * MotorUtil.cpp
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#include <Motor.h>

Motor::Motor(TIM_HandleTypeDef *htim, uint32_t channelA, uint32_t channelB, uint16_t maxCounter)
:htim(htim), channelA(channelA), channelB(channelB), maxCounter(maxCounter){
	// TODO Auto-generated constructor stub

}

void Motor::enable(){
	HAL_TIM_PWM_Start(htim, channelA);
	HAL_TIM_PWM_Start(htim, channelB);
	__HAL_TIM_SET_COMPARE(htim, channelA, 0);
	__HAL_TIM_SET_COMPARE(htim, channelB, 0);
}

void Motor::disable(){
	HAL_TIM_PWM_Stop(htim, channelA);
	HAL_TIM_PWM_Stop(htim, channelB);
}

void Motor::standby(){
	__HAL_TIM_SET_COMPARE(htim, channelA, 0);
	__HAL_TIM_SET_COMPARE(htim, channelB, 0);
}

void Motor::setVelocityInPercent(float velocity){
	if(velocity >= 0){
		__HAL_TIM_SET_COMPARE(htim, channelA, velocity*maxCounter/100);
		__HAL_TIM_SET_COMPARE(htim, channelB, 0);
	}else{
		__HAL_TIM_SET_COMPARE(htim, channelA, 0);
		__HAL_TIM_SET_COMPARE(htim, channelB, -velocity*maxCounter/100);
	}
}

void Motor::brake(){
	volatile const uint16_t counterPeriod = __HAL_TIM_GET_AUTORELOAD(htim);
	__HAL_TIM_SET_COMPARE(htim, channelA, counterPeriod);
	__HAL_TIM_SET_COMPARE(htim, channelB, counterPeriod);
}

int8_t Motor::getPower(){
return (__HAL_TIM_GET_COMPARE(htim, channelA) - __HAL_TIM_GET_COMPARE(htim, channelB))*100/maxCounter;
}
