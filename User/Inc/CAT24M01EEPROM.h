/*
 * CAT24M01EEPROM.h
 *
 *  Created on: Feb 28, 2026
 *      Author: conat
 */

#ifndef INC_CAT24M01EEPROM_H_
#define INC_CAT24M01EEPROM_H_

#include "config.h"
#include "i2c.h"

class CAT24M01_EEPROM {
	I2C_HandleTypeDef *hi2c;
	Config *_config;
	uint8_t address = 0b101000<<2;
public:
	CAT24M01_EEPROM(I2C_HandleTypeDef *hi2c, Config *config):hi2c(hi2c),_config(config){};
	void write();
	void read();
};

#endif /* INC_CAT24M01EEPROM_H_ */
