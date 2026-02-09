#include "commandEvent.hpp"

namespace command{
void sensorStatusTransmitEvent(CommandDataType::SensorStatus &data){
    data.tof() = state.tof == SENSOR_STATE::Normal;
    data.camera() = state.camera == SENSOR_STATE::Normal;
    data.barometer() = state.barometer == SENSOR_STATE::Normal;
    data.magnetmeter() = state.magnetmeter == SENSOR_STATE::Normal;
    data.gps() = state.gps == SENSOR_STATE::Normal;
    data.imu() = state.imu == SENSOR_STATE::Normal;
}

void goalReceiveEvent(CommandDataType::Coordinates &data){
	nmeaProcessor.setReferencePoint(data.latitude(), data.longitude());
}
void goalTransmitEvent(CommandDataType::Coordinates &data){
	auto config = nmeaProcessor.getReferencePoint();
	data.latitude() = config.latitude;
	data.longitude() = config.longitude;
}

void altitudeTransmitEvent(CommandDataType::Altitude &data){
	data.altitude() = altitudeEstimation.getAltitude();
	data.pressure() = barometer.getOutput().pressure;
	data.temperature() = barometer.getOutput().temperature;
}

void modeReceiveEvent(uint8_t data){
	hmode.setMode(static_cast<mode::MODE>(data));
}
void modeTransmitEvent(uint8_t& data){
	data = static_cast<uint8_t>(hmode.getActiveMode());
}

void absoluteNavigationTransmitEvent(CommandDataType::AbsoluteNavigation &data){

}

void relativeNavigationTransmitEvent(CommandDataType::RelativeNavigation &data){

}

void servoConfigParachuteLeftTransmitEvent(CommandDataType::ServoConfig &data){
    if (state.parachuteServoLeft == ACTUATOR_STATE::Disabled){
        data.state() = CommandDataType::ServoState::Disabled;
    }else{
        switch(parachuteServoLeft.getServoState){
            case SERVO_STATE::Release:
                data.state() = CommandDataType::ServoState::Open;
            break;
            case SERVO_STATE::Grip:
                data.state() = CommandDataType::ServoState::Close;
            break;
            case SERVO_STATE::Center:
                data.state() = CommandDataType::ServoState::Center;
            break;
        }
    }
    data.centerCount = parachuteServoLeft.getCenterCount();
    data.openCount = parachuteServoLeft.getReleaseCount();
    data.closeCount = parachuteServoLeft.getGripCount();
}
void servoConfigParachuteLeftReceiveEvent(CommandDataType::ServoConfig &data){
	auto servoConfig = &parachuteServoLeft;
	switch(data.state()){
		case CommandDataType::ServoState::Disabled:
			servoConfig->disable();
			break;
		case CommandDataType::ServoState::Open:
			servoConfig->release();
			break;
		case CommandDataType::ServoState::Close:
			servoConfig->grip();
			break;
		case CommandDataType::ServoState::Center:
			servoConfig->center();
			break;
	}
	servoConfig->setReleaseCount(data.openCount());
	servoConfig->setGripCount(data.closeCount());
	servoConfig->setCenterCount(data.centerCount());
}

void servoConfigParachuteRightTransmitEvent(CommandDataType::ServoConfig &data){
    if (state.parachuteServoRight == ACTUATOR_STATE::Disabled){
        data.state() = CommandDataType::ServoState::Disabled;
    }else{
        switch(parachuteServoRight.getServoState){
            case SERVO_STATE::Release:
                data.state() = CommandDataType::ServoState::Open;
            break;
            case SERVO_STATE::Grip:
                data.state() = CommandDataType::ServoState::Close;
            break;
            case SERVO_STATE::Center:
                data.state() = CommandDataType::ServoState::Center;
            break;
        }
    }
    data.centerCount = parachuteServoRight.getCenterCount();
    data.openCount = parachuteServoRight.getReleaseCount();
    data.closeCount = parachuteServoRight.getGripCount();
}
void servoConfigParachuteRightReceiveEvent(CommandDataType::ServoConfig &data){
	auto servoConfig = &parachuteServoRight;
	switch(data.state()){
		case CommandDataType::ServoState::Disabled:
			servoConfig->disable();
			break;
		case CommandDataType::ServoState::Open:
			servoConfig->release();
			break;
		case CommandDataType::ServoState::Close:
			servoConfig->grip();
			break;
		case CommandDataType::ServoState::Center:
			servoConfig->center();
			break;
	}
	servoConfig->setReleaseCount(data.openCount());
	servoConfig->setGripCount(data.closeCount());
	servoConfig->setCenterCount(data.centerCount());
}

void servoConfigStabilizerTransmitEvent(CommandDataType::ServoConfig &data){
if (state.stabilizerServo == ACTUATOR_STATE::Disabled){
        data.state() = CommandDataType::ServoState::Disabled;
    }else{
        switch(stabilizerServo.getServoState){
            case SERVO_STATE::Release:
                data.state() = CommandDataType::ServoState::Open;
            break;
            case SERVO_STATE::Grip:
                data.state() = CommandDataType::ServoState::Close;
            break;
            case SERVO_STATE::Center:
                data.state() = CommandDataType::ServoState::Center;
            break;
        }
    }
    data.centerCount = stabilizerServo.getCenterCount();
    data.openCount = stabilizerServo.getReleaseCount();
    data.closeCount = stabilizerServo.getGripCount();
}
void servoConfigStabilizerReceiveEvent(CommandDataType::ServoConfig &data){
	auto servoConfig = &stabilizerServo;
	switch(data.state()){
		case CommandDataType::ServoState::Disabled:
			servoConfig->disable();
			break;
		case CommandDataType::ServoState::Open:
			servoConfig->release();
			break;
		case CommandDataType::ServoState::Close:
			servoConfig->grip();
			break;
		case CommandDataType::ServoState::Center:
			servoConfig->center();
			break;
	}
	servoConfig->setReleaseCount(data.openCount());
	servoConfig->setGripCount(data.closeCount());
	servoConfig->setCenterCount(data.centerCount());
}
} /* namespace command */
