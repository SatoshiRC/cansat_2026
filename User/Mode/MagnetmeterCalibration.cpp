/*
 * MagnetmeterCalibration.cpp
 *
 *  Created on: Mar 1, 2026
 *      Author: conat
 */

#include <MagnetmeterCalibration.h>

namespace mode {

MagnetmeterCalibration::MagnetmeterCalibration(command::CommandManager *commandManager, const std::array<float, 3> &magnetOffset)
		:ModeBase(commandManager),magnetOffset(magnetOffset){
	// TODO Auto-generated constructor stub

}

void MagnetmeterCalibration::onImuUpdate(const ImuOutput &imu){

}
void MagnetmeterCalibration::finalize(){

}

} /* namespace mode */
