#ifndef COMMAND_EVENT_HPP
#define COMMAND_EVENT_HPP

#include "Command/Inc/CommandManager.h"
#include "Parachute.h"
#include "Drive.h"
#include "State.h"
#include "NMEA.hpp"
#include "AltitudeEstimation.h"
#include "Barometer.h"
#include "ModeHandler.h"
#include "ICM20948_USER.h"
#include "config.h"
#include "CAT24M01EEPROM.h"

extern ServoGripper parachuteServoLeft;
extern ServoGripper parachuteServoRight;
extern ServoGripper stabilizerServo;
extern Parachute parachute;
extern Drive drive;
extern State state;
extern NMEAProcessor nmeaProcessor;
extern AltitudeEstimation altitudeEstimation;
extern Barometer barometer;
extern mode::ModeHandler hmode;
extern ICM20948_HAL icm20948;
extern Config config;
extern CAT24M01_EEPROM eeprom;

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

void gpsTransmitEvent(CommandDataType::GPS &data);

void imuTransmitEvent(CommandDataType::IMU &data);

void saveConfingReceiveEvent();

void decentLogTransmitEvent(CommandDataType::DecentLog &data);
} /* namespace command */

#endif /* COMMAND_EVENT_HPP */
