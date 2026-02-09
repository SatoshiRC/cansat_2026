#include "commandEvent.hpp"

namespace command{
void sensorStatusTransmitEvent(CommandDataType::SensorStatus &data){

}

void goalReceiveEvent(CommandDataType::Coordinates &data){

}
void goalTransmitEvent(CommandDataType::Coordinates &data){

}

void altitudeTransmitEvent(CommandDataType::Altitude &data){

}

void modeReceiveEvent(uint8_t data){

}
void modeTransmitEvent(uint8_t& data){

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

}
} /* namespace command */