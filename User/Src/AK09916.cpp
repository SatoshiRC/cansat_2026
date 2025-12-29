/*
 * AK09916.cpp
 *
 *  Created on: Feb 21, 2024
 *      Author: heila
 */

#include "AK09916.h"


AK09916::AK09916() {
	// TODO Auto-generated constructor stub
}

/*void AK09916::setupICM(I2C_HandleTypeDef hi2c2){
    uint8_t ICM_productID=0;
    while(ICM_productID!=0xea){
    	HAL_Delay(100);
    	HAL_I2C_Mem_Read(&hi2c2, 0x68<<1, 0x00, 1, &ICM_productID, 1, 100);
		if(hi2c2.ErrorCode){
			print("i2c error code"+std::to_string(hi2c2.ErrorCode)+"\n");
		}
    }

    uint8_t power1_data=0x01;
    HAL_I2C_Mem_Write(&hi2c2, 0x68<<1, 0x06, 1, &power1_data, 1, 100);

    uint8_t dis_accel_and_gyro=0b00111111;
    HAL_I2C_Mem_Write(&hi2c2, 0x68<<1, 0x07, 1, &dis_accel_and_gyro, 1, 100);

    uint8_t set_status_passthrough=0x80;
    HAL_I2C_Mem_Write(&hi2c2, 0x68<<1, 0x17, 1, &set_status_passthrough, 1, 100);
}*/

float AK09916::getMagnet_X(void) {
	uint8_t tmp[2];
	readBytes(REGISTER::HXL, tmp, 2);
	uint16_t rawMagnet=tmp[1]<<8 | tmp[0];
	return rawMagnet;
}

float AK09916::getMagnet_Y(void) {
	uint8_t tmp[2];
	readBytes(REGISTER::HYL, tmp, 2);
	uint16_t rawMagnet=tmp[1]<<8 | tmp[0];
	return rawMagnet;
}

float AK09916::getMagnet_Z(void) {
	uint8_t tmp[2];
	readBytes(REGISTER::HZL, tmp, 2);
	uint16_t rawMagnet=tmp[1]<<8 | tmp[0];
	return rawMagnet;
}

void AK09916::setMesurementMode(MODE mode){
	writeByte(REGISTER::CNTL2, (uint8_t)mode);
}
/*
bool AK09916::DatareadisReady(){
	uint8_t DRDY=0;
	readByte()
}
*/

