/*
 * AK09916.h
 *
 *  Created on: Feb 21, 2024
 *      Author: heila
 */

#ifndef INC_AK09916_H_
#define INC_AK09916_H_

#include <stdint.h>
#include <array>

class AK09916 {
public:
    enum class REGISTER{
        WIA2=0x01,
        ST1=0x10,
        HXL,
        HXH,
        HYL,
        HYH,
        HZL,
        HZH,
		ST2=0x18,
        CNTL2=0x31,
        CNTL3
    };

    enum class MODE{
        Power_down,
        single_measurement,
        mode1,      //10hz
        mode2=0x04,      //20hz
        mode3=0x06,      //50hz
        mode4=0x08,      //100hz
        self_test=0x10
    };


    AK09916();
    //void setupICM(I2C_HandleTypeDef hi2c2);
    float getMagnet_X(void);
    float getMagnet_Y(void);
    float getMagnet_Z(void);

    bool DatareadisReady();
    void setMesurementMode(MODE mode);

    virtual uint8_t readByte(REGISTER reg){return 0;}
    virtual void writeByte(REGISTER reg, uint8_t value){}
    virtual void readBytes(REGISTER reg, uint8_t *pData, uint8_t size=1){}

protected:
    uint8_t setBit(uint8_t arg, uint8_t position, bool value=true);
    uint8_t resetBit(uint8_t arg, uint8_t position);


};

#endif /* INC_AK09916_H_ */
