/*
 * GPS.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satosih
 */

#include <GPS.h>

GPS::GPS(SensorState *state, NMEAProcessor *nmeaProcessor, UART_HandleTypeDef *huart)
:state(state), nmeaProcessor(nmeaProcessor), huart(huart){

}

void GPS::startReceive(){
	HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t*)rBuffer.data(), rBuffer.size());
}

void GPS::onReceive(){
	uint16_t rxCount = huart->RxXferCount;
	std::vector<uint8_t> rMessage(rBuffer.begin(), rBuffer.begin()+rxCount);
	nmeaProcessor->onReceive(rMessage);
	if(nmeaProcessor->isLastFrameValid()){
		*state = SENSOR_STATE::Normal;
	}
}
