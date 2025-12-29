/*
 * Wrapper.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include "Wrapper.hpp"

#include "usart.h"
#include "tim.h"
#include "gpio.h"

#include "GPS.h"
#include "NMEA.hpp"
#include "State.h"
#include "elapsedTimer/elapsedTimer.h"
#include "SwEventCalback.hpp"
#include "Parachute.h"
#include "Motor.h"
#include "Drive.h"

#include "ModeHandler.h"
#include "ModeWakeUp.h"
#include "ModeReady.h"
#include "ModeDecent.h"
#include "ModeRemoteControl.h"

#include <array>

ElapsedTimer elapsedTimer(&htim2);


ServoGripper parachuteServoLeft;
ServoGripper parachuteServoRight;
ServoGripper stabilizerServo;
Motor leftMotor;
Motor rightMotor;
GPS gps;
Barometer barometer;

Parachute parachute;
Drive drive;
NMEAProcessor nmeaProcessor;

State state;

ModeWakeUp modeWakeUp;
ModeReady modeReady;
ModeDecent modeDecent;
ModeRemoteControl modeRemoteControl;
ModeHandler hmode;

void init(){
	//activate and check low-layer application
	if(!elapsedTimer.selfTest()){
		//TODO : elapsed timer error
	}
	state = State(&elapsedTimer);

	//configure callback functions
	//TODO : configure callback functions
	nmeaProcessor.setPositionCallback(onGpsPositionUpdate);

	//construct mode handler
	modeWakeUp = ModeWakeUp();
	modeReady = ModeReady();
	modeDecent = ModeDecent(&parachute);
	modeRemoteControl = ModeRemoteControl(&parachute, &stabilizerServo, &drive);

	//construct low-layer features
	gps = GPS(&state.GPS, &nmeaProcessor);

	parachuteServoLeft = ServoGripper(&state.parachuteServoLeft, &htim13, TIM_CHANNEL_1);
	parachuteServoRight = ServoGripper(&state.parachuteServoRight, &htim2, TIM_CHANNEL_1);
	stabilizerServo = ServoGripper(&state.stabilizerServo, &htim14, TIM_CHANNEL_1);

	//configure and activate features
	parachute = Parachute(&parachuteServoLeft, &parachuteServoRight);
	parachute.enable();
	drive = Drive(&leftMotor, &rightMotor);
	drive.enable();
	//TODO : configure ICM20948
	//TODO : configure AK09916 which is implemented in the ICM20948
	//TODO : configure LPS25HB

}

void loop(){
	hmode.executeInloop();
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(huart == gps.getHuart()){
		if(huart->RxEventType == HAL_UART_RXEVENT_IDLE){
			gps.onReceive();
		}
	}
}
