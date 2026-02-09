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

class ModeAltitudeEstimationTest {
	MODE mode;
	AltitudeEstimation _altitudeEstimation = nullptr;
protected:
	MODE nextMode;
public:
	ModeAltitudeEstimationTest() = default;
	ModeAltitudeEstimationTest(AltitudeEstimation *altitudeEstimation, MODE mode = MODE::AttitudeEstimationTest);
	void initialize(){};
	void execute(){};
	void onImuUpdate(){};
	void onAltitudeUpdate(const uint16_t altitude){};

	MODE getNextMode();
};

}

#endif /* INC_MODE_ALTITUDE_ESTIMATION_TEST_H_ */
