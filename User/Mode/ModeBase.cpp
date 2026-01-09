/*
 * StateBase.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

#include <ModeBase.h>

namespace mode{

ModeBase::ModeBase(MODE mode)
:mode(mode),nextMode(mode){
	// TODO Auto-generated constructor stub

}

MODE ModeBase::getNextMode(){
	return nextMode;
}

}
