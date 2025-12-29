/*
 * Barometer.h
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_BAROMETER_H_
#define INC_BAROMETER_H_

#include <cstdint>
#include <functional>

struct BarometerOutput{
	float pressure = 0;
	float temperature = 0;
};

class Barometer {
	std::function<void(const BarometerOutput&)> _callback;
public:
	Barometer();

	void setCallback(std::function<void(const BarometerOutput&)> callback);
};

#endif /* INC_BAROMETER_H_ */
