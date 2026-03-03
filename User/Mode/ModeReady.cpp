/*
 * ModeReady.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeReady.h>

namespace mode{

Ready::Ready(command::CommandManager *commandManager, Config *config)
:ModeBase(commandManager),
 config(config)
{
	// TODO Auto-generated constructor stub

}

void Ready::initialize(){
	nextMode = mode;
}

void Ready::execute(){

}

void Ready::onAltitudeUpdate(const uint16_t altitude){
	if(altitude > 10*1000){
		nextMode = MODE::DECENT;
	}
}
void Ready::onImuUpdate(const ImuOutput &imu){
	for(uint8_t n=0; n<3; n++){
		if(imu.m[n] > config->magnetMax[n]){
			config->magnetMax[n] = imu.m[n];
			config->magnetOffset[n] = (config->magnetMax[n] + config->magnetMin[n]) / 2;
		}else if(imu.m[n] < config->magnetMin[n]){
			config->magnetMin[n] = imu.m[n];
		}
	}
}

}
