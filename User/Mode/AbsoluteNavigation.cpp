/*
 * AbsoluteNavigation.cpp
 *
 *  Created on: Mar 1, 2026
 *      Author: OHYA Satoshi
 */

#include "AbsoluteNavigation.h"

namespace mode {

AbsoluteNavigation::AbsoluteNavigation(command::CommandManager *commandManager, const std::array<float, 3> &magnetOffset)
		:ModeBase(commandManager), magnetOffset(magnetOffset){
	// TODO Auto-generated constructor stub

}

void AbsoluteNavigation::initialize(){

}

void AbsoluteNavigation::execute(){

}


void AbsoluteNavigation::onGpsUpdate(const NEDPosition &position){
	_targetHeadingDirection = std::atan2(-position.east, position.north);
}

void AbsoluteNavigation::onImuUpdate(const ImuOutput &imu){

}

} /* namespace mode */
