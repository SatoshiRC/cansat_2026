/*
 * ModeGoal.h
 *
 *  Created on: Mar 6, 2026
 *      Author: satoshi
 */

#ifndef MODE_INC_MODEGOAL_H_
#define MODE_INC_MODEGOAL_H_

#include <ModeBase.h>
#include <Drive.h>

namespace mode{
class ModeGoal: public ModeBase {
	static constexpr MODE mode = MODE::GOAL;
	Drive *drive;
public:
	ModeGoal(command::CommandManager *commandManager, Drive *drive);
	void initialize();
	void execute();
	void onAltitudeUpdate(const uint16_t altitude);

	constexpr MODE getMode(){
		return mode;
	}
};

}
#endif /* MODE_INC_MODEGOAL_H_ */
