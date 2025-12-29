/*
 * Parachute.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <Parachute.h>

Parachute::Parachute(ServoGripper *left, ServoGripper *right):left(left),right(right) {
	// TODO Auto-generated constructor stub

}

Parachute::~Parachute(){
	delete left;
	delete right;
}
