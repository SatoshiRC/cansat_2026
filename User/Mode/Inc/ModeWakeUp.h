/*
 * ModeWakeUp.h
 *
 *  Created on: Dec 29, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEWAKEUP_H_
#define INC_MODEWAKEUP_H_

#include <ModeBase.h>

namespace mode{

class WakeUp : public ModeBase {
public:
	WakeUp();

	void execute();
};

}

#endif /* INC_MODEWAKEUP_H_ */
