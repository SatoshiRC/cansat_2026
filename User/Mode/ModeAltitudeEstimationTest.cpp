/*
 * ModeAltitudeEstimationTest.cpp
 *
 *  Created on: Feb 10, 2026
 *      Author: conat
 */


#include "ModeAltitudeEstimationTest.h"

namespace mode{
AltitudeEstimationTest::AltitudeEstimationTest(command::CommandManager *commandManager, AltitudeEstimation *altitudeEstimation)
		:ModeBase(commandManager),_altitudeEstimation(altitudeEstimation){

}
void AltitudeEstimationTest::onAltitudeUpdate(const uint16_t altitude){
	commandManager->transmit(command::COMMAND_ID::Altitude);
	HAL_Delay(2);
	commandManager->transmit(command::COMMAND_ID::GPS);
	HAL_Delay(2);
	commandManager->transmit(command::COMMAND_ID::IMU);
	HAL_Delay(2);
}
void AltitudeEstimationTest::onImuUpdate(const ImuOutput &imu){
}
void AltitudeEstimationTest::onGpsUpdate(const NEDPosition &position){
}
}
