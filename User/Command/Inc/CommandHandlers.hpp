/*
 * CommandHandlers.hpp
 *
 *  Created on: Jan 30, 2026
 *      Author: OHYA Satoshi
 */

#ifndef COMMAND_INC_COMMANDHANDLERS_HPP_
#define COMMAND_INC_COMMANDHANDLERS_HPP_

#include "CommandHandlerBase.h"
#include "DataType.hpp"

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

class SensorStatus : public Base{
    static constexpr uint8_t dataBodyLen = 1;
    static constexpr COMMAND_ID id = COMMAND_ID::SensorStatus;

    CommandDataType::SensorStatus *data = nullptr;
    const uint8_t tofOffset = 5;
    const uint8_t cameraOffset = 4;
    const uint8_t barometerOffset = 3;
    const uint8_t magnetMeterOffset = 2;
    const uint8_t imuOffset = 1;
    const uint8_t gpsOffset = 0;
    
public:
    SensorStatus() = default;
    explicit SensorStatus(CommandDataType::SensorStatus *data):data(data){}
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

    CommandDataType::Coordinates *data = nullptr;

    std::function<void(CommandDataType::Coordinates&)> callback = [](CommandDataType::Coordinates &coordinate) -> void {};

public:
    Goal() = default;
    explicit Goal(CommandDataType::Coordinates *data):data(data){};
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::Coordinates&)> callback){
        this->callback = callback;
    }
};

class Altitude : public Base{
    static constexpr uint8_t dataBodyLen = 10;
    COMMAND_ID id = COMMAND_ID::Altitude;

    CommandDataType::Altitude *data = nullptr;
    std::function<void(CommandDataType::Altitude&)> callback = [](CommandDataType::Altitude& data){};

public:
    Altitude() = default;
    explicit Altitude(CommandDataType::Altitude *data):data(data){}
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::Altitude&)> callback){
        this->callback = callback;
    }
};

class Mode : public Base{
    static constexpr uint8_t dataBodyLen = 1;
    COMMAND_ID id = COMMAND_ID::Mode;

    uint8_t *data = nullptr;
    std::function<void(uint8_t)> callback = [](uint8_t mode){};

public:
    Mode() = default;
    explicit Mode(uint8_t *data):data(data){}
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(uint8_t)> callback){
        this->callback = callback;
    }
};

class AbsoluteNavigation : public Base {
    static constexpr uint8_t dataBodyLen = 10;
    COMMAND_ID id = COMMAND_ID::AbsoluteNavigationLog;

    CommandDataType::AbsoluteNavigation *data = nullptr;
    std::function<void(CommandDataType::AbsoluteNavigation&)> callback = [](CommandDataType::AbsoluteNavigation& data){};

public:
    AbsoluteNavigation() = default;
    explicit AbsoluteNavigation(CommandDataType::AbsoluteNavigation *data):data(data){}
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::AbsoluteNavigation&)> callback){
        this->callback = callback;
    }
};

class RelativeNavigation : public Base {
    static constexpr uint8_t dataBodyLen = 13;
    COMMAND_ID id = COMMAND_ID::RelativeNavigationLog;

    CommandDataType::RelativeNavigation *data = nullptr;
    std::function<void(CommandDataType::RelativeNavigation&)> callback = [](CommandDataType::RelativeNavigation& data){};

public:
    RelativeNavigation() = default;
    explicit RelativeNavigation(CommandDataType::RelativeNavigation *data):data(data){}
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::RelativeNavigation&)> callback){
        this->callback = callback;
    }
};

class ServoConfig : public Base {
    static constexpr uint8_t dataBodyLen = 7;

    CommandDataType::ServoConfig *data = nullptr;
    std::function<void(CommandDataType::ServoConfig&)> callback = [](CommandDataType::ServoConfig& data){};

public:
    ServoConfig() = default;
    explicit ServoConfig(CommandDataType::ServoConfig *data):data(data){}
    COMMAND_ID onReceive(std::vector<uint8_t> &body);
    std::vector<uint8_t> transmit();
    void setCallback(std::function<void(CommandDataType::ServoConfig&)> callback){
        this->callback = callback;
    }
};
class ServoConfig_prachuteLeft : public ServoConfig{
    COMMAND_ID id = COMMAND_ID::ServoConfig_prachuteLeft;
};

class ServoConfig_prachuteRight : public ServoConfig {
    COMMAND_ID id = COMMAND_ID::ServoConfig_prachuteRight;
};
class ServoConfig_stabilizer : public ServoConfig {
    COMMAND_ID id = COMMAND_ID::ServoConfig_stabilizer;
};
} /*namespace command*/

#endif /* COMMAND_INC_COMMANDHANDLERS_HPP_ */