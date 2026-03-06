/*
 * ModeDecent.h
 *
 *  Created on: Dec 23, 2025
 *      Author: OHYA Satoshi
 */

#ifndef INC_MODEDECENT_H_
#define INC_MODEDECENT_H_

#include <ModeBase.h>
#include "Parachute.h"
#include "Drive.h"
#include "elapsedTimer/elapsedTimer.h"

namespace mode{

class Decent: public ModeBase {
	static constexpr MODE mode = MODE::DECENT;
	int16_t parachuteReleaseAlt = 2000;
	Parachute *parachute;
	Drive *drive;
	ServoGripper *stabilizer;
	ElapsedTimer *elapsedTimer;
	CommandDataType::DecentLog commandData;

	enum class Sequence{
		Decent,
		ParachuteRelease,
		StabilizerDeploy,
		nextMode,
		Last,
	};

	std::array<float, 3> sequenceDelay = {0, 5*1000, 5*1000};
	float timeStamp = 0;
	Sequence sequence = Sequence::Decent;
public:
	Decent() = default;
	Decent(command::CommandManager *commandManager, Parachute *parachute, Drive *drive, ServoGripper *stabilizer, ElapsedTimer *elapsedTimer);
	void initialize();
	void execute();
	void onAltitudeUpdate(const uint16_t altitude);

	constexpr MODE getMode(){
		return mode;
	}
};

}

#endif /* INC_MODEDECENT_H_ */
