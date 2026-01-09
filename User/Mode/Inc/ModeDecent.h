/*
 * ModeDecent.h
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEDECENT_H_
#define INC_MODEDECENT_H_

#include <ModeBase.h>
#include "Parachute.h"

namespace mode{

class Decent: public ModeBase {
	int16_t parachuteReleaseAlt;
	Parachute *parachute;
public:
	Decent(Parachute *parachute = nullptr);
	void execute();
	void onAltitudeUpdate(const uint16_t altitude);
};

}

#endif /* INC_MODEDECENT_H_ */
