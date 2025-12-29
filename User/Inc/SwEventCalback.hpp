/*
 * SwEventCalback.hpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#ifndef SWEVENTCALBACK_HPP_
#define SWEVENTCALBACK_HPP_

#include "GPS.h"
#include "NMEA.hpp"
#include "Barometer.h"
#include "State.h"
#include "elapsedTimer/elapsedTimer.h"
#include "ModeHandler.h"

extern ModeHandler hmode;

/*
 * Sensors Callback Function Prototypes
 */
void onGpsPositionUpdate(const NEDPosition &position);
void onBarometerUpdate(const BarometerOutput &barometerOutput);

/*
 * Algorithm Update Callback Function Prototypes
 */
void onAltitudeUpdate(const float altitude);

#endif /* SWEVENTCALBACK_HPP_ */
