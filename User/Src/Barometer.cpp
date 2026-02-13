/*
 * Barometer.cpp
 *
 *  Created on: Dec 27, 2025
 *      Author: OHYA Satoshi
 */

#include <Barometer.h>

Barometer::Barometer(LPS25HB_STM32_HAL *lps25hb, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
:lps25hb(lps25hb), GPIOx(GPIOx), GPIO_Pin(GPIO_Pin)
{
	// TODO Auto-generated constructor stub
	_output = BarometerOutput();

}

void Barometer::init(){
	lps25hb->begin(LPS25HB::LPS25HB_FIFO_MODE::BYPASS_MODE, LPS25HB::LPS25HB_RATE::F25Hz);
	lps25hb->writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG3), 0);
	lps25hb->writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG4), 0b1); //Data ready int
	lps25hb->writeData(static_cast<uint8_t>(LPS25HB_REG::INTERRUPT_CFG), 0);
}

void Barometer::update(){
	_output.pressure = lps25hb->getPressure();
	_output.temperature = lps25hb->getTemplature();
	_callback(_output);
}

void Barometer::setCallback(std::function<void(const BarometerOutput&)> callback){
	_callback = callback;
}
