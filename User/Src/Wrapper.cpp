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

#include "Command/Inc/CommandManager.h"
#include "commandEvent.hpp"


#include <array>

ElapsedTimer elapsedTimer(&htim2);
State state(&elapsedTimer);
Config config;

ServoGripper parachuteServoLeft(&state.parachuteServoRight, &htim13, TIM_CHANNEL_1, &config.parachuteLeft);
ServoGripper parachuteServoRight(&state.parachuteServoRight, &htim2, TIM_CHANNEL_1, &config.parachuteRight);
ServoGripper stabilizerServo(&state.stabilizerServo, &htim14, TIM_CHANNEL_1, &config.stabilizer);
Motor leftMotor;
Motor rightMotor;
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

mode::WakeUp modeWakeUp(&commandManager, &nmeaProcessor, &altitudeEstimation);
mode::Ready modeReady;
mode::Decent modeDecent(&commandManager, &parachute, &drive, &elapsedTimer);
mode::RemoteControl modeRemoteControl(&commandManager, &parachute, &stabilizerServo, &drive, &elapsedTimer);
mode::AltitudeEstimationTest modeAltitudeEstimationTest(&commandManager, &altitudeEstimation);
mode::AbsoluteNavigation modeAbsoluteNavigation(&commandManager, config.magnetOffset);
mode::ModeHandler hmode(&commandManager, &config, &eeprom);

std::array<uint8_t, 64> usbTxBuffer;

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
    commandManager[command::COMMAND_ID::ServoConfig_stabilizer] = static_cast<command::Base*>(&servoConfigStabilizer);
	commandManager[command::COMMAND_ID::GPS] = static_cast<command::Base*>(&gpsCommand);
	commandManager[command::COMMAND_ID::IMU] = static_cast<command::Base*>(&imuCommand);

	//set up mode handler
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeWakeUp));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeReady));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeDecent));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeRemoteControl));
	hmode.registerMode(static_cast<mode::ModeBase*>(&modeAltitudeEstimationTest));

	if(config.activeMode >= static_cast<uint8_t>(mode::MODE::DECENT) && config.activeMode <= static_cast<uint8_t>(mode::MODE::GOAL)){
		// resume operation
		modeWakeUp.resumeFrom(static_cast<mode::MODE>(config.activeMode));
	}

	//construct low-layer features
	gps.startReceive();

	//configure and activate features
	parachute.enable();
	parachute.grip();
	stabilizerServo.enable();
	stabilizerServo.grip();
	drive.enable();


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

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

}

void loop(){
	altitudeEstimation.exeEstimation();
	hmode.executeInloop();
	gps.startReceive();
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)){
		lps25hb.updateRawData();
	}
}

void usbCdcReceive(uint8_t* first, uint8_t* last){
	commandManager.receive(first, last);
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

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
//	if(huart == gps.getHuart()){
//		if(huart->RxEventType == HAL_UART_RXEVENT_TC){
//			gps.onReceive(huart->RxXferSize - huart->RxXferCount);
//		}else if(huart->RxEventType == HAL_UART_RXEVENT_IDLE){
//			gps.onReceive();
//		}
//	}
}

void UART2_RX_Byte(){
	UART_HandleTypeDef *huart = &huart2;
	gps.onReceive(huart->RxXferSize - huart->RxXferCount);
}

//void command::CommandManager::forceTransmit(const COMMAND_ID id){
////	if(isTransmitting == true){
////		return;
////	}
//
//	if(id == command::COMMAND_ID::Last){
//		return;
//	}
//	uint8_t frameLen = 0;
//	constructTransmitFrameToBuffer(id, usbTxBuffer.data(), frameLen);
//
//	uint8_t ret = 0;
//	do{
//		ret = (CDC_Transmit_FS(static_cast<uint8_t*>(usbTxBuffer.begin()), frameLen));
//	}while(ret);
//}


void command::CommandManager::transmit(const COMMAND_ID id){
//	if(isTransmitting == true){
//		return;
//	}

	if(id == command::COMMAND_ID::Last){
		return;
	}
	uint8_t frameLen = 0;
	constructTransmitFrameToBuffer(id, usbTxBuffer.data(), frameLen);
	CDC_Transmit_FS(static_cast<uint8_t*>(usbTxBuffer.begin()), frameLen);
}
