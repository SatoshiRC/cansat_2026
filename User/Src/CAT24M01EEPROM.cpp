/*
 * CAT24M01EEPROM.cpp
 *
 *  Created on: Feb 28, 2026
 *      Author: conat
 */

#include <CAT24M01EEPROM.h>

void CAT24M01_EEPROM::write(){
	auto data = _config->convertToArray();

	HAL_I2C_Mem_Write(hi2c, address, 0, 2, (uint8_t*)data.data(), data.size(), 500);
}

void CAT24M01_EEPROM::read(){
	std::array<uint8_t, Config::len> data;

	HAL_I2C_Mem_Read(hi2c, address, 0, 2, data.data(), Config::len, 500);
	_config->parseArray(data);
}

