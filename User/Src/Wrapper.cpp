/*
 * Wrapper.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include "Wrapper.hpp"
#include "gpio.h"
#include "usart.h"
#include "tim.h"

#include "GPS.h"
#include "NMEA.hpp"
#include "State.h"
#include "elapsedTimer/elapsedTimer.h"
#include "SwEventCalback.hpp"
#include "Parachute.h"
#include "Motor.h"
#include "Drive.h"
#include "ICM20948_USER.h"
#include "CAT24M01EEPROM.h"

#include "ModeHandler.h"
#include "ModeWakeUp.h"
#include "ModeReady.h"
#include "ModeDecent.h"
#include "ModeRemoteControl.h"
#include "ModeAltitudeEstimationTest.h"
#include "AbsoluteNavigation.h"
#include "ModeGoal.h"

#include "Command/Inc/CommandManager.h"
#include "commandEvent.hpp"


#include <array>

ElapsedTimer elapsedTimer(&htim5);
State state(&elapsedTimer);
Config config;

ServoGripper parachuteServoLeft(&state.parachuteServoRight, &htim13, TIM_CHANNEL_1, &config.parachuteLeft);
ServoGripper parachuteServoRight(&state.parachuteServoRight, &htim2, TIM_CHANNEL_1, &config.parachuteRight);
ServoGripper stabilizerServo(&state.stabilizerServo, &htim14, TIM_CHANNEL_1, &config.stabilizer);
Motor leftMotor(&htim3, TIM_CHANNEL_4, TIM_CHANNEL_3, 1000);
Motor rightMotor(&htim3, TIM_CHANNEL_2, TIM_CHANNEL_1, 1000);
GPS gps(&state.gps, &nmeaProcessor);
LPS25HB_STM32_HAL lps25hb(&hi2c2, LPS25HB::LPS25HB_Address::Low);
ICM20948_HAL icm20948(&hi2c1, ICM20948::Address::LOW);
CAT24M01_EEPROM eeprom(&hi2c1, &config);

Parachute parachute(&parachuteServoLeft, &parachuteServoRight);
Drive drive(&leftMotor, &rightMotor);
Barometer barometer = Barometer(&lps25hb, GPIOB, GPIO_PIN_2);
NMEAProcessor nmeaProcessor;
AltitudeEstimation altitudeEstimation;
ICM20948_USER imu(&icm20948, GPIO_PIN_3);

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
command::ServoConfig_stabilizer servoConfigStabilizer;
command::Gps gpsCommand;
command::Imu imuCommand;
command::DecentLog decentLog;

mode::WakeUp modeWakeUp(&commandManager, &nmeaProcessor, &altitudeEstimation);
mode::Ready modeReady(&commandManager, &config);
mode::Decent modeDecent(&commandManager, &parachute, &drive, &stabilizerServo, &elapsedTimer);
mode::RemoteControl modeRemoteControl(&commandManager, &parachute, &stabilizerServo, &drive, &elapsedTimer);
mode::AltitudeEstimationTest modeAltitudeEstimationTest(&commandManager, &altitudeEstimation);
mode::AbsoluteNavigation modeAbsoluteNavigation(&commandManager, &elapsedTimer, &drive, &config);
mode::ModeGoal modeGoal(&commandManager, &drive);
mode::ModeHandler hmode(&commandManager, &config, &eeprom);

std::array<uint8_t, 64> usbTxBuffer;
std::array<uint8_t, 64> xbeeRxBuffer = {};
std::array<uint8_t, 10> tofBuffer = {};
std::array<uint8_t, 6> jevoisBuffer = {};

void init(){
	imu.disableIntPin();
	barometer.disableIntPin();

	//activate and check low-layer application
	if(!elapsedTimer.selfTest()){
		//TODO : elapsed timer error
	}

	eeprom.read();
	nmeaProcessor.setReferencePoint(config.goal.latitude, config.goal.longitude);

	//configure callback functions
	//TODO : configure callback functions
	nmeaProcessor.setPositionCallback(onGpsPositionUpdate);
	altitudeEstimation.setCallback(onAltitudeUpdate);

	//bind event handler
    altitude.setUpdate(command::altitudeTransmitEvent);
    modeCommandHandler.setCallback(command::modeReceiveEvent);
    modeCommandHandler.setUpdate(command::modeTransmitEvent);
    gpsCommand.setUpdate(command::gpsTransmitEvent);
    imuCommand.setUpdate(command::imuTransmitEvent);
    servoConfigParachuteLeft.setCallback(command::servoConfigParachuteLeftReceiveEvent);
    servoConfigParachuteLeft.setUpdate(command::servoConfigParachuteLeftTransmitEvent);
    servoConfigParachuteRight.setCallback(command::servoConfigParachuteRightReceiveEvent);
	servoConfigParachuteRight.setUpdate(command::servoConfigParachuteRightTransmitEvent);
	servoConfigStabilizer.setCallback(command::servoConfigStabilizerReceiveEvent);
	servoConfigStabilizer.setUpdate(command::servoConfigStabilizerTransmitEvent);
	goal.setCallback(command::goalReceiveEvent);
	goal.setUpdate(command::goalTransmitEvent);
	decentLog.setCallback(command::decentLogTransmitEvent);
	relativeNavigation.setUpdate(command::relativeNavigationTransmitEvent);
	decentLog.setUpdate(command::decentLogTransmitEvent);
	absoluteNavigation.setUpdate(command::absoluteNavigationTransmitEvent);
	relativeNavigation.setUpdate(command::relativeNavigationTransmitEvent);
	
	//set up commands
	commandManager[command::COMMAND_ID::ConnectionCheck] = static_cast<command::Base*>(&connectionCheck);
    commandManager[command::COMMAND_ID::SensorStatus] = static_cast<command::Base*>(&sensorStatus);
    commandManager[command::COMMAND_ID::Request] = static_cast<command::Base*>(&request);
    commandManager[command::COMMAND_ID::Goal] = static_cast<command::Base*>(&goal);
    commandManager[command::COMMAND_ID::Altitude] = static_cast<command::Base*>(&altitude);
    commandManager[command::COMMAND_ID::Mode] = static_cast<command::Base*>(&modeCommandHandler);
    commandManager[command::COMMAND_ID::DecentLog] = static_cast<command::Base*>(&decentLog);
    commandManager[command::COMMAND_ID::AbsoluteNavigationLog] = static_cast<command::Base*>(&absoluteNavigation);
    commandManager[command::COMMAND_ID::RelativeNavigationLog] = static_cast<command::Base*>(&relativeNavigation);
    commandManager[command::COMMAND_ID::ServoConfig_prachuteLeft] = static_cast<command::Base*>(&servoConfigParachuteLeft);
    commandManager[command::COMMAND_ID::ServoConfig_prachuteRight] = static_cast<command::Base*>(&servoConfigParachuteRight);
    commandManager[command::COMMAND_ID::ServoConfig_stabilizer] = static_cast<command::Base*>(&servoConfigStabilizer);
	commandManager[command::COMMAND_ID::GPS] = static_cast<command::Base*>(&gpsCommand);
	commandManager[command::COMMAND_ID::IMU] = static_cast<command::Base*>(&imuCommand);

	//set up mode handler
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeWakeUp));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeReady));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeDecent));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeAbsoluteNavigation));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeRemoteControl));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeAltitudeEstimationTest));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeGoal));

	if(config.activeMode >= static_cast<uint8_t>(mode::MODE::DECENT) && config.activeMode <= static_cast<uint8_t>(mode::MODE::GOAL)){
		// resume operation
		modeWakeUp.resumeFrom(static_cast<mode::MODE>(config.activeMode));
	}
	modeWakeUp.initialize();


	//construct low-layer features
	gps.startReceive();

	//configure and activate features
	parachute.enable();
	parachute.grip();
	stabilizerServo.enable();
	stabilizerServo.grip();
	drive.enable();
	drive.brake();


	barometer.setCallback(onBarometerUpdate);
	barometer.init();
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)){
		lps25hb.updateRawData();
	}
	barometer.enableIntPin();

	imu.confirmConnection();
	imu.init();
	imu.setCallback(onImuUpdate);
	imu.enableIntPin();

	//start tof receive;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart6, tofBuffer.data(), tofBuffer.size());
	HAL_UARTEx_ReceiveToIdle_IT(&huart4, jevoisBuffer.data(), jevoisBuffer.size());

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

}

void loop(){
	commandManager.processReceive();
	altitudeEstimation.exeEstimation();
	hmode.executeInloop();
	gps.startReceive();
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)){
		lps25hb.updateRawData();
	}
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, xbeeRxBuffer.data(), xbeeRxBuffer.size());
	HAL_UARTEx_ReceiveToIdle_DMA(&huart6, tofBuffer.data(), tofBuffer.size());
	HAL_UARTEx_ReceiveToIdle_IT(&huart4, jevoisBuffer.data(), jevoisBuffer.size());
}

void usbCdcReceive(uint8_t* first, uint8_t* last){

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
switch(GPIO_Pin){
case GPIO_PIN_2:
	lps25hb.updateRawData();
	break;
case GPIO_PIN_3:
	icm20948.readImuDma();
	break;
default:
	break;
}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	if(hi2c == &hi2c1){
		state.imu = SENSOR_STATE::Normal;
		imu.update();
	}else if(hi2c == &hi2c2){
		state.barometer = SENSOR_STATE::Normal;
		barometer.update();
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size){
//	if(huart == gps.getHuart()){
//		if(huart->RxEventType == HAL_UART_RXEVENT_TC){
//			gps.onReceive(huart->RxXferSize - huart->RxXferCount);
//		}else if(huart->RxEventType == HAL_UART_RXEVENT_IDLE){
//			gps.onReceive();
//		}
//	}
	if(huart == &huart1){
		//xbee callback
		commandManager.receive(xbeeRxBuffer.data(),xbeeRxBuffer.data()+size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, xbeeRxBuffer.data(), xbeeRxBuffer.size());
	}else if(huart == &huart6){
		uint16_t tofLen = 0xffff;
		if(tofBuffer[0] == 'R' && tofBuffer[4] == '\r'){
			std::string str(tofBuffer.begin()+1, tofBuffer.begin()+4);
			tofLen = std::stoi(str);
			modeAbsoluteNavigation.onTofUpdate(tofLen);
		}else if(tofBuffer[0] == 'R' && tofBuffer[3] == '\r'){
			std::string str(tofBuffer.begin()+1, tofBuffer.begin()+3);
			tofLen = std::stoi(str);
			modeAbsoluteNavigation.onTofUpdate(tofLen);
		}
		HAL_UARTEx_ReceiveToIdle_DMA(huart, tofBuffer.data(), tofBuffer.size());
	}else if(huart == &huart4){
		if(jevoisBuffer[0] == 's' && jevoisBuffer[3] == 'e'){
			modeAbsoluteNavigation.onCameraUpdate(jevoisBuffer[2], jevoisBuffer[1]);
		}
		HAL_UARTEx_ReceiveToIdle_IT(huart, jevoisBuffer.data(), jevoisBuffer.size());
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart6){
		uint16_t tofLen = 0xffff;
		if(tofBuffer[0] == 'R' && tofBuffer[4] == '\r'){
			std::string str(tofBuffer.begin()+1, tofBuffer.end()-1);
			tofLen = std::stoi(str);
			modeAbsoluteNavigation.onTofUpdate(tofLen);
		}
		HAL_UARTEx_ReceiveToIdle_DMA(huart, tofBuffer.data(), tofBuffer.size());
	}else if(huart == &huart4){
		if(jevoisBuffer[0] == 's' && jevoisBuffer[3] == 'e'){
			modeAbsoluteNavigation.onCameraUpdate(jevoisBuffer[2], jevoisBuffer[1]);
		}
		HAL_UARTEx_ReceiveToIdle_IT(huart, jevoisBuffer.data(), jevoisBuffer.size());
	}
}

void UART2_RX_Byte(){
	UART_HandleTypeDef *huart = &huart2;
	gps.onReceive(huart->RxXferSize - huart->RxXferCount);
}


void command::CommandManager::transmit(const COMMAND_ID id){
//	if(isTransmitting == true){
//		return;
//	}

	if(id == command::COMMAND_ID::Last){
		return;
	}
	uint8_t frameLen = 0;
	constructTransmitFrameToBuffer(id, usbTxBuffer.data(), frameLen);
	HAL_UART_Transmit_DMA(&huart1, usbTxBuffer.data(), frameLen);
}
