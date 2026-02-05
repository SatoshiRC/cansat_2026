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

    CommandDataType::SensorStatus *status;
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

    CommandDataType::Coordinates data;

    std::function<void(CommandDataType::Coordinates&)> callback = [](CommandDataType::Coordinates &coordinate) -> void {};

public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::Coordinates&)> callback){
        this->callback = callback;
    }
};

class Altitude : public Base{
    static constexpr uint8_t dataBoodyLen = 10;
    COMMAND_ID id = COMMAND_ID::Altitude;

    CommandDataType::Altitude data;
    std::function<void(CommandDataType::Altitude&)> callback = [](CommandDataType::Altitude& data){};

public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::Altitude&)> callback){
        this->callback = callback;
    }
};

class Mode : public Base{
    static constexpr uint8_t dataBodyLen = 1;
    COMMAND_ID id = COMMAND_ID::Mode;

    std::function<void(uint8_t)> callback = [](uint8_t mode){};

public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(uint8_t)> callback){
        this->callback = callback;
    }
};

class AbsoluteNavigation : public Base {
    static constexpr uint8_t dataBodyLen = 10;
    COMMAND_ID id = COMMAND_ID::AbsoluteNavigationLog;

    CommandDataType::AbsoluteNavigation *data;
    std::function<void(CommandDataType::AbsoluteNavigation&)> callback = [](CommandDataType::AbsoluteNavigation& data){};

public:
COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::AbsoluteNavigation&)> callback){
        this->callback = callback;
    }
};

class RelativeNavigation : public Base {
    static constexpr uint8_t dataBodyLen = 13;
    COMMAND_ID id = COMMAND_ID::RelativeNavigationLog;

    CommandDataType::RelativeNavigation *data;
    std::function<void(CommandDataType::RelativeNavigation&)> callback = [](CommandDataType::RelativeNavigation& data){};

public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::RelativeNavigation&)> callback){
        this->callback = callback;
    }
};

class ServoConfig_prachuteLeft : public Base {
    static constexpr uint8_t dataBodyLen = 7;
    COMMAND_ID id = COMMAND_ID::ServoConfig_prachuteLeft;

    CommandDataType::SservoConfig *data;
    std::function<void(CommandDataType::SservoConfig&)> callback = [](CommandDataType::SservoConfig& data){};

public:
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::SservoConfig&)> callback){
        this->callback = callback;
    }
};
class ServoConfig_prachuteRight : public ServoConfig_prachuteLeft {
    COMMAND_ID id = COMMAND_ID::ServoConfig_prachuteRight;
};
class ServoConfig_stabilizer : public ServoConfig_prachuteLeft {
    COMMAND_ID id = COMMAND_ID::ServoConfig_stabilizer;
};
} /*namespace command*/

#endif /* COMMAND_INC_COMMANDHANDLERS_HPP_ */