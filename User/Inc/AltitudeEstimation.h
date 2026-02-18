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
#include <cmath>
#include "Barometer.h"

class AltitudeEstimation {
	uint16_t _altitude = 0;
	std::function<void(const uint16_t)> _callback;

	bool _isCompleteCalibration = false;

	uint16_t grouncPressureCalibrationCount = 0;
	float groundPressure = 0;
	BarometerOutput _befBarometerOunput;
public:
	AltitudeEstimation() = default;
	AltitudeEstimation(std::function<void(const uint16_t)> callback):_callback(callback){}
	void onObserveBarometer(const BarometerOutput &barometerOutput);
	void onObserveGPS();
	void onObserveIMU();
	void exeEstimation();

	uint16_t getAltitude();
	bool isCompleteCalibration(){return _isCompleteCalibration;}
	void setCallback(std::function<void(const uint16_t)> callback);
};

#endif /* INC_ALTITUDEESTIMATION_H_ */
