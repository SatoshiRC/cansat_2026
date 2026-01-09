/*
 * ModeReady.h
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEREADY_H_
#define INC_MODEREADY_H_

#include <ModeBase.h>

namespace mode{

class Ready : public ModeBase {
public:
	Ready();
	void execute();

};

}

#endif /* INC_MODEREADY_H_ */
