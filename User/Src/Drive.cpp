/*
 * Drive.cpp
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#include <Drive.h>

Drive::Drive() {
	// TODO Auto-generated constructor stub
	_left = nullptr;
	_right = nullptr;
}

Drive::Drive(Motor *left, Motor *right)
:_left(left),_right(right){

}

void Drive::enable(){
	_isEnable = true;
	_left->enable();
	_right->enable();
}

void Drive::disable(){
	_isEnable = false;
}

void Drive::drive(DriveVelocity velocity){
	_left->setVelocityInPercent(velocity.velocity - velocity.angularVelocity);
	_right->setVelocityInPercent(velocity.velocity + velocity.angularVelocity);
}

void Drive::brake(){
	_left->brake();
	_right->brake();
}
