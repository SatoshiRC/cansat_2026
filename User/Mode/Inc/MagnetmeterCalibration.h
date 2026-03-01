/*
 * MagnetmeterCalibration.h
 *
 *  Created on: Mar 1, 2026
 *      Author: conat
 */

#ifndef MODE_INC_MAGNETMETERCALIBRATION_H_
#define MODE_INC_MAGNETMETERCALIBRATION_H_

#include <ModeBase.h>

namespace mode {

class MagnetmeterCalibration: public ModeBase {
	static constexpr MODE mode = MODE::ABSOLUTE_NAVIGATION;
	const std::array<float, 3> &magnetOffset;
public:
	MagnetmeterCalibration(command::CommandManager *commandManager, const std::array<float, 3> &magnetOffset);
	void onImuUpdate(const ImuOutput &imu);
	void finalize();
};

} /* namespace mode */

#endif /* MODE_INC_MAGNETMETERCALIBRATION_H_ */
