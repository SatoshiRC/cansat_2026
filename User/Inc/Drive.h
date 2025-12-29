/*
 * Drive.h
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_DRIVE_H_
#define INC_DRIVE_H_

#include <Motor.h>

struct DriveVelocity{
	float velocity = 0;
	float angularVelocity = 0;
};

class Drive {
	Motor *_left;
	Motor *_right;
	bool _isEnable = false;
public:
	Drive();
	Drive(Motor *left, Motor *right);
	Motor* left(){
		return _left;
	}
	Motor* right(){
		return _right;
	}

	void enable();
	void disable();

	void drive(DriveVelocity velocity);
	void brake();
};

#endif /* INC_DRIVE_H_ */
