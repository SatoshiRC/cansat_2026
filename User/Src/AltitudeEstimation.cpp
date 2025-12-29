/*
 * AltitudeEstimation.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <AltitudeEstimation.h>

AltitudeEstimation::AltitudeEstimation()
:_altitude(0){
	// TODO Auto-generated constructor stub
}

uint16_t AltitudeEstimation::getAltitude(){
	return _altitude;
}

void AltitudeEstimation::setCallback(std::function<void(const uint16_t)> callback){
	_callback = callback;
}
