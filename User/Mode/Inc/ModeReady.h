/*
 * ModeReady.h
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEREADY_H_
#define INC_MODEREADY_H_

#include <ModeBase.h>
#include "config.h"

namespace mode{

class Ready : public ModeBase {
	static constexpr MODE mode = MODE::READY;
	Config *config;
public:
	Ready() = default;
	Ready(command::CommandManager *commandManager, Config *config);
	void initialize();
	void execute();
	void onAltitudeUpdate(const uint16_t altitude);
	void onImuUpdate(const ImuOutput &imu);

	constexpr MODE getMode(){
		return mode;
	}

};

}

#endif /* INC_MODEREADY_H_ */
