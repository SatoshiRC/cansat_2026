/*
 * AbsoluteNavigation.h
 *
 *  Created on: Mar 1, 2026
 *      Author: OHYA Satoshi
 */

#ifndef MODE_ABSOLUTENAVIGATION_H_
#define MODE_ABSOLUTENAVIGATION_H_

#include <numbers>

#include <ModeBase.h>
#include "Drive.h"
#include "config.h"
#include "elapsedTimer/elapsedTimer.h"

namespace mode {

class AbsoluteNavigation: public ModeBase {
	static constexpr MODE mode = MODE::ABSOLUTE_NAVIGATION;

	Drive *drive;
	const Config *config;
	ElapsedTimer *timer;

	static constexpr uint8_t baseSpeed = 50;
	static constexpr float relativeNavigationStartTh = 2;
	static constexpr float absoluteNavigationStartTh = 6;

	enum class Sequence{
		absoluteNavigation,
		relativeNavigation_search0,
		relativeNavigation_search1,
		relativeNavigation_search2,
		relativeNavigation_search3,
		relativeNavigation_search4,
		relativeNavigation_search5,
		relativeNavigation_search6,
		relativeNavigation_search7,
		relativeNavigation,
		goal,
	}sequence;

	std::array<float, 3> magnetGain;

	float _targetHeadingDirection;
	float _headingDirection;
	float distance;
	float sequenceTransitionTimeStamp;
	float startTimeStamp;
	float directionFromCamera = 0;
	bool isGoalDetectedByCamera = false;
	uint16_t distanceMeasuredByTof = 0;
	bool isGoalDetectedByTof = false;

public:
	AbsoluteNavigation(command::CommandManager *commandManager, ElapsedTimer *elapsedTimer,Drive *drive, const Config *config);
	void initialize();
	void execute();
	void onGpsUpdate(const NEDPosition &position);
	void onImuUpdate(const ImuOutput &imu);
	void onCameraUpdate(int8_t direction, bool isDetected){
		isGoalDetectedByCamera = isDetected;
		directionFromCamera = direction*std::numbers::pi/180.0;
	}
	void onTofUpdate(uint16_t distance, bool isDetected){
		isGoalDetectedByTof = isDetected;
		distanceMeasuredByTof = distance;
	}
	constexpr MODE getMode(){
		return mode;
	}
};

} /* namespace mode */

#endif /* MODE_ABSOLUTENAVIGATION_H_ */
