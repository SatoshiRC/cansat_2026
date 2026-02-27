/*
 * GPS.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include <vector>
#include <functional>

#include "usart.h"

#include "NMEA.hpp"
#include "State.h"

class GPS {
	SensorState *state;
	NMEAProcessor *nmeaProcessor;
	UART_HandleTypeDef *huart;

	std::array<uint8_t, 100> rBuffer;
	std::function<void(NEDPosition)> nedPositionHandler;
public:
	GPS(SensorState *state = nullptr, NMEAProcessor *nmeaProcessor = nullptr, UART_HandleTypeDef *huart = &huart2);
	void startReceive();
	void onReceive(uint16_t count);
	void onReceive();

	constexpr UART_HandleTypeDef *getHuart(){
		return huart;
	}
};

#endif /* INC_GPS_H_ */
