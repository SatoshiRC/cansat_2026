/*
 * ModeHandler.h
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEHANDLER_H_
#define INC_MODEHANDLER_H_

#include <array>

#include "ModeBase.h"

namespace mode {

class ModeHandler {
	std::array<ModeBase*, 9> modeHandlers;
	MODE activeMode;
public:
	ModeHandler();
	void executeInloop();
	void onGpsUpdate(const NEDPosition &position){};
	void onImuUpdate(){};
	void onAltitudeUpdate(const float altitude){};

	void registerMode(MODE id, ModeBase *mode);
	void setMode(MODE mode);
	MODE getActiveMode(){
		return activeMode;
	}
};

}  // namespace mode

#endif /* INC_MODEHANDLER_H_ */
