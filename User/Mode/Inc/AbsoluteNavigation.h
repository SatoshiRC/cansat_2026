/*
 * AbsoluteNavigation.h
 *
 *  Created on: Mar 1, 2026
 *      Author: OHYA Satoshi
 */

#ifndef MODE_ABSOLUTENAVIGATION_H_
#define MODE_ABSOLUTENAVIGATION_H_

#include <ModeBase.h>

namespace mode {

class AbsoluteNavigation: public ModeBase {
	static constexpr MODE mode = MODE::ABSOLUTE_NAVIGATION;
	 const std::array<float, 3> &magnetOffset;

	 float _targetHeadingDirection;
	 float _headingDirection;
public:
	AbsoluteNavigation(command::CommandManager *commandManager, const std::array<float, 3> &magnetOffset);
	void initialize();
	void execute();
	void onGpsUpdate(const NEDPosition &position);
	void onImuUpdate(const ImuOutput &imu);
};

} /* namespace mode */

#endif /* MODE_ABSOLUTENAVIGATION_H_ */
