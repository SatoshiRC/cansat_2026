/*
 * Wrapper.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include "Wrapper.hpp"
#include "usbd_cdc_if.h"
#include "gpio.h"

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
#include "ModeAltitudeEstimationTest.h"

#include "Command/Inc/CommandManager.h"
#include "commandEvent.hpp"

#include <array>

ElapsedTimer elapsedTimer(&htim2);


ServoGripper parachuteServoLeft;
ServoGripper parachuteServoRight;
ServoGripper stabilizerServo;
Motor leftMotor;
Motor rightMotor;
GPS gps;
LPS25HB_STM32_HAL lps25hb;

Parachute parachute;
Drive drive;
Barometer barometer;
NMEAProcessor nmeaProcessor;
AltitudeEstimation altitudeEstimation;

State state;

mode::WakeUp modeWakeUp;
mode::Ready modeReady;
mode::Decent modeDecent;
mode::RemoteControl modeRemoteControl;
mode::AltitudeEstimationTest modeAltitudeEstimationTest;
mode::ModeHandler hmode;

command::CommandManager commandManager;
command::ConnectionCheck connectionCheck;
command::SensorStatus sensorStatus;
command::Request request;
command::Goal goal;
command::Altitude altitude;
command::Mode modeCommandHandler;
command::AbsoluteNavigation absoluteNavigation;
command::RelativeNavigation relativeNavigation;
command::ServoConfig_prachuteLeft servoConfigParachuteLeft;
command::ServoConfig_prachuteRight servoConfigParachuteRight;
command::ServoConfig_stabilizer servoConfigStavilizer;
command::Gps gpsCommand;

std::array<uint8_t, 64> usbTxBuffer;

void init(){
	//activate and check low-layer application
	if(!elapsedTimer.selfTest()){
		//TODO : elapsed timer error
	}
	state = State(&elapsedTimer);

	//configure callback functions
	//TODO : configure callback functions
	nmeaProcessor.setPositionCallback(onGpsPositionUpdate);
	altitudeEstimation.setCallback(onAltitudeUpdate);

	//bind event handler
    altitude.setUpdate(command::altitudeTransmitEvent);
    modeCommandHandler.setCallback(command::modeReceiveEvent);
    modeCommandHandler.setUpdate(command::modeTransmitEvent);
    gpsCommand.setUpdate(command::gpsTransmitEvent);
	
	//set up commands
	commandManager[command::COMMAND_ID::ConnectionCheck] = static_cast<command::Base*>(&connectionCheck);
    commandManager[command::COMMAND_ID::SensorStatus] = static_cast<command::Base*>(&sensorStatus);
    commandManager[command::COMMAND_ID::Request] = static_cast<command::Base*>(&request);
    commandManager[command::COMMAND_ID::Goal] = static_cast<command::Base*>(&goal);
    commandManager[command::COMMAND_ID::Altitude] = static_cast<command::Base*>(&altitude);
    commandManager[command::COMMAND_ID::Mode] = static_cast<command::Base*>(&modeCommandHandler);
    commandManager[command::COMMAND_ID::AbsoluteNavigationLog] = static_cast<command::Base*>(&absoluteNavigation);
    commandManager[command::COMMAND_ID::RelativeNavigationLog] = static_cast<command::Base*>(&relativeNavigation);
    commandManager[command::COMMAND_ID::ServoConfig_prachuteLeft] = static_cast<command::Base*>(&servoConfigParachuteLeft);
    commandManager[command::COMMAND_ID::ServoConfig_prachuteRight] = static_cast<command::Base*>(&servoConfigParachuteRight);
    commandManager[command::COMMAND_ID::ServoConfig_stabilizer] = static_cast<command::Base*>(&servoConfigStavilizer);
	commandManager[command::COMMAND_ID::GPS] = static_cast<command::Base*>(&gpsCommand);

	//construct mode handler
	modeWakeUp = mode::WakeUp(&nmeaProcessor, &altitudeEstimation);
	modeReady = mode::Ready();
	modeDecent = mode::Decent(&commandManager, &parachute);
	modeRemoteControl = mode::RemoteControl(&commandManager, &parachute, &stabilizerServo, &drive, &elapsedTimer);
	modeAltitudeEstimationTest = mode::AltitudeEstimationTest(&commandManager, &altitudeEstimation);

	hmode = mode::ModeHandler(&commandManager);
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeWakeUp));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeReady));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeDecent));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeRemoteControl));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeAltitudeEstimationTest));

	hmode.setMode(mode::MODE::WAKE_UP);

	//construct low-layer features
	gps = GPS(&state.gps, &nmeaProcessor);
	lps25hb = LPS25HB_STM32_HAL(&hi2c2, LPS25HB::LPS25HB_Address::Low);

	parachuteServoLeft = ServoGripper(&state.parachuteServoLeft, &htim13, TIM_CHANNEL_1);
	parachuteServoRight = ServoGripper(&state.parachuteServoRight, &htim2, TIM_CHANNEL_1);
	stabilizerServo = ServoGripper(&state.stabilizerServo, &htim14, TIM_CHANNEL_1);

	//configure and activate features
	parachute = Parachute(&parachuteServoLeft, &parachuteServoRight);
	parachute.enable();

	drive = Drive(&leftMotor, &rightMotor);
	drive.enable();

	barometer = Barometer(&lps25hb, GPIOB, GPIO_PIN_2);
	barometer.disableIntPin();
	barometer.setCallback(onBarometerUpdate);
	barometer.init();
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)){
		lps25hb.updateRawData();
	}
	barometer.enableIntPin();
	//TODO : configure ICM20948
	//TODO : configure AK09916 which is implemented in the ICM20948

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

}

void loop(){
	altitudeEstimation.exeEstimation();
	hmode.executeInloop();
}

void usbCdcReceive(uint8_t* first, uint8_t* last){
	commandManager.receive(first, last);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
switch(GPIO_Pin){
case GPIO_PIN_2:
	lps25hb.updateRawData();
	break;
default:
	break;
}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c == &hi2c1){

	}else if(hi2c == &hi2c2){
		barometer.update();
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(huart == gps.getHuart()){
		if(huart->RxEventType == HAL_UART_RXEVENT_IDLE){
			gps.onReceive();
		}
	}
}

void command::CommandManager::transmit(const COMMAND_ID id){
	if(id == command::COMMAND_ID::Last){
		return;
	}
	auto frame = constructTransmitFrame(id);
	std::copy(frame.begin(), frame.end(), usbTxBuffer.begin());
	CDC_Transmit_FS(static_cast<uint8_t*>(usbTxBuffer.begin()), frame.size());
}
