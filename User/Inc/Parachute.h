/*
 * Parachute.h
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_PARACHUTE_H_
#define INC_PARACHUTE_H_

#include "ServoGripper.h"

class Parachute {
	ServoGripper *left;
	ServoGripper *right;
public:
	Parachute(ServoGripper *left = nullptr, ServoGripper *right = nullptr);
	~Parachute();

	void enable(){
		left->enable();
		right->enable();
	}
	void disable(){
		left->disable();
		right->disable();
	}

	void release(){
		left->release();
		right->release();
	}
	void releaseLeft(){
		left->release();
	}
	void releaseRight(){
		right->release();
	}

	void grip(){
		left->grip();
		right->grip();
	}
	void gripLeft(){
		left->grip();
	}
	void gripRight(){
		right->grip();
	}

};

#endif /* INC_PARACHUTE_H_ */
