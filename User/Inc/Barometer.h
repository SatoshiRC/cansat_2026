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
#include "LPS25HB.h"

struct BarometerOutput{
	float pressure = 0;
	float temperature = 0;
};

class Barometer {
	std::function<void(const BarometerOutput&)> _callback = [](const BarometerOutput&){};
	BarometerOutput _output;
	LPS25HB_STM32_HAL *lps25hb;

public:
	Barometer() = default;
	Barometer(LPS25HB_STM32_HAL *lps25hb);
	void init();
	void update();

	void setCallback(std::function<void(const BarometerOutput&)> callback);
	BarometerOutput& getOutput(){return _output;}
	const BarometerOutput& getOutput() const {return _output;}
};

#endif /* INC_BAROMETER_H_ */
