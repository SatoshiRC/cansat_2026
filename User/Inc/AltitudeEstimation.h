/*
 * AltitudeEstimation.h
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_ALTITUDEESTIMATION_H_
#define INC_ALTITUDEESTIMATION_H_

#include <cstdint>
#include <functional>

class AltitudeEstimation {
	uint16_t _altitude;
	std::function<void(const uint16_t)> _callback;
public:
	AltitudeEstimation();
	void onObserveBarometer();
	void onObserveGPS();
	void onObserveIMU();
	void exeEstimation();

	uint16_t getAltitude();
	void setCallback(std::function<void(const uint16_t)> callback);
};

#endif /* INC_ALTITUDEESTIMATION_H_ */
