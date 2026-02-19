/*
 * ModeWakeUp.h
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEWAKEUP_H_
#define INC_MODEWAKEUP_H_

#include <ModeBase.h>
#include "NMEA.hpp"
#include "AltitudeEstimation.h"

namespace mode{

class WakeUp : public ModeBase {
	MODE mode = MODE::WAKE_UP;
	NMEAProcessor *nmeaProcessor = nullptr;
	AltitudeEstimation *altitudeEstimation  = nullptr;
public:
	WakeUp() = default;
	WakeUp(NMEAProcessor *nmeaProcessor,
			AltitudeEstimation *altitudeEstimation)
	:nmeaProcessor(nmeaProcessor),
	 altitudeEstimation(altitudeEstimation){}

	void initialize();
	void execute();
	void onGpsUpdate(const NEDPosition &position);

	constexpr MODE getMode(){
		return mode;
	}
};

}

#endif /* INC_MODEWAKEUP_H_ */
