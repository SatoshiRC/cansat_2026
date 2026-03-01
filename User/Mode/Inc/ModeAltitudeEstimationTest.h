/*
 * StateBase.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODE_ALTITUDE_ESTIMATION_TEST_H_
#define INC_MODE_ALTITUDE_ESTIMATION_TEST_H_

#include "ModeBase.h"
#include "State.h"
#include "GPS.h"
#include "AltitudeEstimation.h"

namespace mode{

class AltitudeEstimationTest : public ModeBase {
	static constexpr MODE mode = MODE::Debug;
	AltitudeEstimation *_altitudeEstimation = nullptr;
protected:
	MODE nextMode;
public:
	AltitudeEstimationTest() = default;
	AltitudeEstimationTest(command::CommandManager *commandManager, AltitudeEstimation *altitudeEstimation);
	void initialize(){};
	void execute(){};
	void onImuUpdate(const ImuOutput &imu);
	void onAltitudeUpdate(const uint16_t altitude);
	void onGpsUpdate(const NEDPosition &position);

	constexpr MODE getMode(){
		return mode;
	}
};

}

#endif /* INC_MODE_ALTITUDE_ESTIMATION_TEST_H_ */
