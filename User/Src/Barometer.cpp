/*
 * Barometer.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <Barometer.h>

Barometer::Barometer() {
	// TODO Auto-generated constructor stub

}

void Barometer::setCallback(std::function<void(const BarometerOutput&)> callback){
	_callback = callback;
}
