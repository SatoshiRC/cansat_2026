/*
 * CommandHandler.h
 *
 *  Created on: Jan 5, 2026
 *      Author: OHYA Satoshi
 */

#ifndef COMMAND_INC_COMMANDMANAGER_H_
#define COMMAND_INC_COMMANDMANAGER_H_

#include <CommandHandlerBase.h>
#include <CommandHandlers.hpp>
#include <array>
#include <algorithm>

namespace command {

class CommandManager {
	std::array<command::Base*, (uint8_t)COMMAND_ID::Last> commandHandlers;
	static constexpr std::array<uint8_t, (uint8_t)COMMAND_ID::Last> commandLen = {
		ConnectionCheck::getDataBodyLen()
	};

	constexpr uint8_t getMaxBufferLen(){
		return *std::max_element(commandLen.begin(), commandLen.end());
	}

public:
	CommandManager();
	Base& operator[](COMMAND_ID id){
		return *commandHandlers[static_cast<uint8_t>(id)];
	}
};

} /* namespace command */

#endif /* COMMAND_INC_COMMANDMANAGER_H_ */
