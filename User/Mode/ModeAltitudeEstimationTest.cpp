/*
 * ModeAltitudeEstimationTest.cpp
 *
 *  Created on: Feb 10, 2026
 *      Author: conat
 */


#include "ModeAltitudeEstimationTest.h"

namespace mode{
AltitudeEstimationTest::AltitudeEstimationTest(command::CommandManager *commandManager, AltitudeEstimation *altitudeEstimation)
		:ModeBase(commandManager),_altitudeEstimation(altitudeEstimation){

}
}
