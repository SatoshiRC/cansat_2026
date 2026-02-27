/*
 * SwEventCallback.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include "SwEventCalback.hpp"

void onGpsPositionUpdate(const NEDPosition &position){
	//TODO: Implement the callback function
	hmode.onGpsUpdate(position);
	state.gps = SENSOR_STATE::Normal;
}

void onBarometerUpdate(const BarometerOutput &barometerOutput){
	altitudeEstimation.onObserveBarometer(barometerOutput);
}

void onAltitudeUpdate(const float altitude){
	hmode.onAltitudeUpdate(altitude);
}

void onImuUpdate(const ImuOutput &imuOutput){
	hmode.onImuUpdate(imuOutput);
}
