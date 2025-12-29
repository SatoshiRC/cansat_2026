/*
 * State.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

#include "elapsedTimer/elapsedTimer.h"

enum class SENSOR_STATE{
	None = 0,
	Failer,
	Normal,
};

enum class ACTUATOR_STATE{
	None = 0,
	Disabled,
	Active,
	Failer,
};

struct SensorState{
	SensorState(ElapsedTimer *timer = nullptr):timer(timer){}

	SENSOR_STATE state = SENSOR_STATE::None;
	uint64_t lastUpdateTic = 0;

	void operator=(SENSOR_STATE state){
		this->state = state;
		lastUpdateTic = timer->getCount();
	}
private:
	ElapsedTimer *timer;
};

struct ActuatorState{
	ActuatorState(ElapsedTimer *timer = nullptr):timer(timer){}

	ACTUATOR_STATE state = ACTUATOR_STATE::None;
	uint64_t lastUpdateTic = 0;

	void operator=(ACTUATOR_STATE state){
		this->state = state;
		lastUpdateTic = timer->getCount();
	}

private:
	ElapsedTimer *timer;
};

struct State {
	State(ElapsedTimer *timer = nullptr):timer(timer){
		tof = SensorState(timer);
		camera = SensorState(timer);
		barometer = SensorState(timer);
		magnetmeter = SensorState(timer);
		imu  = SensorState(timer);
		gps = SensorState(timer);

		parachuteServoLeft = ActuatorState(timer);
		parachuteServoRight = ActuatorState(timer);
		stabilizerServo = ActuatorState(timer);
		motorLeft = ActuatorState(timer);
		motorRight = ActuatorState(timer);
	};

	SensorState tof;
	SensorState camera;
	SensorState barometer;
	SensorState magnetmeter;
	SensorState imu;
	SensorState gps;

	ActuatorState parachuteServoLeft;
	ActuatorState parachuteServoRight;
	ActuatorState stabilizerServo;
	ActuatorState motorLeft;
	ActuatorState motorRight;
private:
	ElapsedTimer *timer;
};

bool operator==(SensorState first, SENSOR_STATE second);
bool operator==(ActuatorState first, ACTUATOR_STATE second);

#endif /* INC_STATE_H_ */
