/*
 * CommandHandlers.cpp
 *
 *  Created on: Jan 30, 2026
 *      Author: OHYA Satoshi
 */

#include "CommandHandlers.hpp"

namespace command{

COMMAND_ID ConnectionCheck::onReceive(std::vector<uint8_t> &body){
    if (body[0] >> 7 == 1){
        value = 0b0111111 & body[0];
        isLoopback = true;
    }else{
        value = 0b0111111 & body[0];
        isLoopback = false;
    }

    callback();

    return id;
}

std::vector<uint8_t> ConnectionCheck::transmit(){
    std::vector<uint8_t> res(dataBodyLen);
    res[0] = value & ((1*!isLoopback) << 7);

    return res;
}

COMMAND_ID SencorStatus::onReceive(std::vector<uint8_t> &body){

}

std::vector<uint8_t> SencorStatus::transmit(){
    std::vector<uint8_t> res(dataBodyLen);
    res[0] &= tof << tofOffset;
    res[0] &= camera << cameraOffset;
    res[0] &= barometer << barometerOffset;
    res[0] &= magnetMeter << magnetMeterOffset;
    res[0] &= imu << imuOffset;
    res[0] &= tof << tofOffset;
}

COMMAND_ID Request::onReceive(std::vector<uint8_t> &body){
    return static_cast<COMMAND_ID>(body[0]);
}

std::vector<uint8_t> Request::transmit(){
    std::vector<uint8_t> res(dataBodyLen);
    res[0] = static_cast<uint8_t>(requestID);
}

COMMAND_ID Goal::onReceive(std::vector<uint8_t> &body){
    double latitude;
    double longitude;

    std::copy(body.begin(), body.begin()+8, &latitude);
    std::copy(body.begin()+8, body.begin()+16, &longitude);
    callback(latitude, longitude);
    
    return COMMAND_ID::Last;
}

} /*namespace command*/


