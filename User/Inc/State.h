/*
 * State.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

enum class SENSOR_STATE{
	None = 0,
	Failer,
	Normal,
};

struct SensorState{
	SENSOR_STATE state = SENSOR_STATE::None;

};

class State {
	SENSOR_STATE ToF = SENSOR_STATE::None;
	SENSOR_STATE Camera = SENSOR_STATE::None;
	SENSOR_STATE Barometer = SENSOR_STATE::None;
	SENSOR_STATE Magnetmeter = SENSOR_STATE::None;
	SENSOR_STATE IMU = SENSOR_STATE::None;
	SENSOR_STATE GPS = SENSOR_STATE::None;
public:
	State();
};

#endif /* INC_STATE_H_ */
