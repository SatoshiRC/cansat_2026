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

class ModeHandler {
	std::array<*ModeBase, 8> modeHandlers;
public:
	ModeHandler();
};

#endif /* INC_MODEHANDLER_H_ */
