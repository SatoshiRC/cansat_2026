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
}

void onBarometerUpdate(const BarometerOutput &barometerOutput){

}

void onAltitudeUpdate(const float altitude){
	hmode.onAltitudeUpdate(altitude);
}
