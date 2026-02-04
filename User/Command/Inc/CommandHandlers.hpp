/*
 * CommandHandlers.hpp
 *
 *  Created on: Jan 30, 2026
 *      Author: OHYA Satoshi
 */

#ifndef COMMAND_INC_COMMANDHANDLERS_HPP_
#define COMMAND_INC_COMMANDHANDLERS_HPP_

#include <CommandHandlerBase.h>
#include <DataType.hpp>

namespace command{

class ConnectionCheck : public Base{
    static constexpr uint8_t dataBodyLen = 1;
    static constexpr COMMAND_ID id = COMMAND_ID::ConnectionCheck;

    uint8_t value = 0;
    bool isLoopback = false;
    
public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
	std::vector<uint8_t> transmit();
};

class SencorStatus : public Base{
    static constexpr uint8_t dataBodyLen = 1;
    static constexpr COMMAND_ID id = COMMAND_ID::SencorStatus;

    bool tof, camera, barometer, magnetMeter, imu, gps;
    const uint8_t tofOffset = 5;
    const uint8_t cameraOffset = 4;
    const uint8_t barometerOffset = 3;
    const uint8_t magnetMeterOffset = 2;
    const uint8_t imuOffset = 1;
    const uint8_t gpsOffset = 0;
    
public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
	std::vector<uint8_t> transmit();
};

class Request : public Base{
    static constexpr uint8_t dataBodyLen = 1;
    static constexpr COMMAND_ID id = COMMAND_ID::Request;

    COMMAND_ID requestID = COMMAND_ID::Last;
public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
	std::vector<uint8_t> transmit();

    void setRequestCommandId(COMMAND_ID id){
        requestID = id;
    }
};

class Goal : public Base{
    static constexpr uint8_t dataBodyLen = 16;
	COMMAND_ID id = COMMAND_ID::Goal;

    std::function<void(double, double)> callback = [](double latitude, double longitude) -> void {};

public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
};
} /*namespace command*/

#endif /* COMMAND_INC_COMMANDHANDLERS_HPP_ */