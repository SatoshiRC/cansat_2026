/*
 * ModeDecent.cpp
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeDecent.h>

ModeDecent::ModeDecent(State *state, Parachute *parachute)
:ModeBase(MODE::DECENT),parachute(parachute) {

}

ModeDecent::onAltitudeUpdate(const uint16_t altitude){
	if(altitude < parachuteReleaseAlt){
		parachute->release();
		nextMode = MODE::LANDING;
	}
}

