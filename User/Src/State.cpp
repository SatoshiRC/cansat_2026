/*
 * State.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include <State.h>

bool operator==(SensorState first, SENSOR_STATE second){
	return first.state == second;
}

bool operator==(ActuatorState first, ACTUATOR_STATE second){
	return first.state == second;
}
