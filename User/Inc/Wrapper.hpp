/*
 * Wrapper.hpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#ifndef USR_INC_WRAPPER_HPP_
#define USR_INC_WRAPPER_HPP_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void init();
void loop();

void usbCdcReceive(uint8_t* first, uint8_t* last);

#ifdef __cplusplus
};
#endif



#endif /* USR_INC_WRAPPER_HPP_ */
