/*
 * AK09916HALI2C.cpp
 *
 *  Created on: Feb 21, 2024
 *      Author: heila
 */

#ifdef USE_HAL_DRIVER

#include "AK09916_HAL_I2C.h"
#include <array>

AK09916_HAL_I2C::AK09916_HAL_I2C(I2C_HandleTypeDef *hi2c)
:hi2c(hi2c){
	AK09916();
}

uint8_t AK09916_HAL_I2C::readByte(REGISTER reg){
	return readByte((uint8_t)reg);
}

uint8_t AK09916_HAL_I2C::readByte(uint8_t reg){
	uint8_t res=0;
	uint8_t i2cAddress=0b00011000;
	HAL_I2C_Mem_Read(hi2c, i2cAddress, reg, 1, &res, 1, 100);
	return res;
}

//I tried to write code of writeByte
void AK09916_HAL_I2C::writeByte(REGISTER reg, uint8_t value){
	uint8_t i2cAddress=0b00011001;
	HAL_I2C_Mem_Write(hi2c, i2cAddress, (uint8_t)reg, 1, &value, 1, 100);
}

void AK09916_HAL_I2C::readBytes(REGISTER reg, uint8_t *pData, uint8_t size){
	uint8_t i2cAddress=0b00011000;
	HAL_I2C_Mem_Read(hi2c, i2cAddress, (uint8_t)reg, 1, pData, size, 100);
}

#endif
