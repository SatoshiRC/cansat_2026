/*
 * config.cpp
 *
 *  Created on: Mar 1, 2026
 *      Author: OHYA Satoshi
 */

#include "config.h"

std::array<uint8_t, Config::len> Config::convertToArray(){
	std::array<uint8_t, len> res = {};

	uint8_t offset = 0;
	auto servoArray = parachuteLeft.convertToArray();
	std::copy(servoArray.begin(), servoArray.end() ,res.begin()+offset);
	offset += 6;
	servoArray = parachuteRight.convertToArray();
	std::copy(servoArray.begin(), servoArray.end() ,res.begin()+offset);
	offset += 6;
	servoArray = stabilizer.convertToArray();
	std::copy(servoArray.begin(), servoArray.end() ,res.begin()+offset);
	offset += 6;

	uint8_t *p = (uint8_t*)&goal.latitude;
	std::copy(p, p+8, res.begin()+offset);
	offset+=8;
	p = (uint8_t*)&goal.longitude;
	std::copy(p, p+8, res.begin()+offset);
	offset+=8;

	std::copy(&activeMode, &activeMode+1, res.begin()+offset);
	offset+=1;

	std::copy((uint8_t*)magnetOffset.begin(),(uint8_t*)magnetOffset.end(), res.begin()+offset);
	offset += 12;


	return res;
}

void Config::parseArray(std::array<uint8_t, len>& data){
	uint8_t offset = 0;
	parachuteLeft.parse(data.data()+offset, data.data()+offset+6);
	offset += 6;
	parachuteRight.parse(data.data()+offset, data.data()+offset+6);
	offset += 6;
	stabilizer.parse(data.data()+offset, data.data()+offset+6);
	offset += 6;

	uint8_t *p = (uint8_t*)&goal.latitude;
	std::copy(data.data()+offset, data.data()+offset+8, p);
	offset+=8;
	p = (uint8_t*)&goal.longitude;
	std::copy(data.data()+offset, data.data()+offset+8, p);
	offset += 8;

	std::copy(data.data()+offset, data.data()+offset+1, &activeMode);
	offset += 1;

	std::copy(data.data()+offset, data.data()+offset+12, p);
	offset += 12;

}

