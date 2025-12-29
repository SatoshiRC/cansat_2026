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

class ModeDecent: public ModeBase {
	int16_t parachuteReleaseAlt;
	Parachute *parachute;
public:
	ModeDecent(Parachute *parachute = nullptr);
	MODE execute();
};

#endif /* INC_MODEDECENT_H_ */
