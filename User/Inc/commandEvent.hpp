#ifndef COMMAND_EVENT_HPP
#define COMMAND_EVENT_HPP

#include "CommandManager.h"
#include "Parachute.h"
#include "State.h"
#include "NMEA.hpp"
#include "AltitudeEstimation.h"
#include "Barometer.h"
#include "ModeHandler.h"

extern ServoGripper parachuteServoLeft;
extern ServoGripper parachuteServoRight;
extern ServoGripper stabilizerServo;
extern Parachute parachute;
extern State state;
extern NMEAProcessor nmeaProcessor;
extern AltitudeEstimation altitudeEstimation;
extern Barometer barometer;
extern mode::ModeHandler hmode;

namespace command{
void sensorStatusTransmitEvent(CommandDataType::SensorStatus &data);

void goalReceiveEvent(CommandDataType::Coordinates &data);
void goalTransmitEvent(CommandDataType::Coordinates &data);

void altitudeTransmitEvent(CommandDataType::Altitude &data);

void modeReceiveEvent(uint8_t data);
void modeTransmitEvent(uint8_t& data);

void absoluteNavigationTransmitEvent(CommandDataType::AbsoluteNavigation &data);

void relativeNavigationTransmitEvent(CommandDataType::RelativeNavigation &data);

void servoConfigParachuteLeftTransmitEvent(CommandDataType::ServoConfig &data);
void servoConfigParachuteLeftReceiveEvent(CommandDataType::ServoConfig &data);

void servoConfigParachuteRightTransmitEvent(CommandDataType::ServoConfig &data);
void servoConfigParachuteRightReceiveEvent(CommandDataType::ServoConfig &data);

void servoConfigStabilizerTransmitEvent(CommandDataType::ServoConfig &data);
void servoConfigStabilizerReceiveEvent(CommandDataType::ServoConfig &data);
} /* namespace command */

#endif /* COMMAND_EVENT_HPP */
