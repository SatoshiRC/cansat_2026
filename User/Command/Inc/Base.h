/*
 * Base.h
 *
 *  Created on: Jan 5, 2026
 *      Author: OHYA Satoshi
 */

#ifndef COMMAND_BASE_H_
#define COMMAND_BASE_H_

#include <cstdint>
#include <vector>
#include <functional>

namespace command {

class Base {
	std::function<void(void)> _callback;
public:
	Base();
	std::vector<uint8_t> onReceive(std::vector<uint8_t> &body){};

};

} /* namespace command */

#endif /* COMMAND_BASE_H_ */
