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
	MODE mode = MODE::WAKE_UP;
public:
	WakeUp();

	void execute();

	constexpr MODE getMode(){
		return mode;
	}
};

}

#endif /* INC_MODEWAKEUP_H_ */
