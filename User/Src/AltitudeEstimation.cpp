/*
 * AltitudeEstimation.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <AltitudeEstimation.h>

uint16_t AltitudeEstimation::getAltitude(){
	return _altitude;
}

void AltitudeEstimation::setCallback(std::function<void(const uint16_t)> callback){
	_callback = callback;
}

void AltitudeEstimation::onObserveBarometer(const BarometerOutput &barometerOutput){
	if(_isCompleteCalibration == false){
		grouncPressureCalibrationCount++;
		float pressureDiff = (barometerOutput.pressure - groundPressure);
		groundPressure += pressureDiff / grouncPressureCalibrationCount;
		if(grouncPressureCalibrationCount > 10 && std::abs(pressureDiff) > grouncPressureCalibrationCount*0.01){
			groundPressure = 0;
			grouncPressureCalibrationCount = 0;
		}
		if(grouncPressureCalibrationCount>1000){
			_isCompleteCalibration = true;
		}
		return;
	}else{
		_befBarometerOunpur = barometerOutput;
	}
}

void AltitudeEstimation::exeEstimation(){
	if(_befBarometerOunpur.pressure == 0){
		return;
	}
	_altitude = ((groundPressure/_befBarometerOunpur.pressure)^1/5.257 - 1)*(_befBarometerOunpur.temperature + 273.15)/0.0065*1000;
	_befBarometerOunpur = BarometerOutput();
	_callback(_altitude);
}
