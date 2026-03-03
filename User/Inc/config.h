/*
 * config.h
 *
 *  Created on: Feb 28, 2026
 *      Author: conat
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "NMEA.hpp"
#include <array>

struct ServoGripperConfig{
	uint16_t releaseCount;
	uint16_t centerCount;
	uint16_t gripCount;

	ServoGripperConfig(
			uint16_t releaseCount = 1200,
			uint16_t centerCount = 1200,
			uint16_t gripCount = 1200
			)
		:releaseCount(releaseCount),
		centerCount(centerCount),
		gripCount(gripCount){}

	std::array<uint8_t, 6> convertToArray(){
		std::array<uint8_t, 6> res = {};
		std::copy((uint8_t*)&releaseCount, (uint8_t*)&releaseCount+2, res.data());
		std::copy((uint8_t*)&centerCount, (uint8_t*)&centerCount+2, res.data()+2);
		std::copy((uint8_t*)&gripCount, (uint8_t*)&gripCount+2, res.data()+4);

		return res;
	}

	void parse(uint8_t* begin, uint8_t* end){
		std::copy(begin, begin+2, (uint8_t*)&releaseCount);
		std::copy(begin+2, begin+4, (uint8_t*)&centerCount);
		std::copy(begin+4, begin+6, (uint8_t*)&gripCount);
	}
};

struct Goal {
    double latitude;   // 緯度（度）
    double longitude;  // 経度（度）
};

struct Config{
	ServoGripperConfig parachuteLeft;
	ServoGripperConfig parachuteRight;
	ServoGripperConfig stabilizer;

	Goal goal;
	uint8_t activeMode;

	std::array<float, 3> magnetOffset;
	std::array<float, 3> magnetMax;
	std::array<float, 3> magnetMin;

	static constexpr uint8_t len = 6*3 + 16 + 1 + 12*3;
	std::array<uint8_t, len> convertToArray();
	void parseArray(std::array<uint8_t, len>& data);

};

#endif /* INC_CONFIG_H_ */
