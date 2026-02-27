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
	HAL_UARTEx_ReceiveToIdle_IT(huart, (uint8_t*)rBuffer.data(), rBuffer.size());
}

void GPS::onReceive(uint16_t count){
	if(rBuffer[count-2] == '\r' && rBuffer[count-1] == '\n'){
		onReceive();
	}
}

void GPS::onReceive(){
	uint16_t rxCount = huart->RxXferSize - huart->RxXferCount;
	std::vector<uint8_t> rMessage(rBuffer.begin(), rBuffer.begin()+rxCount);
	nmeaProcessor->onReceive(rMessage);
	if(nmeaProcessor->isLastFrameValid()){
		*state = SENSOR_STATE::Normal;
	}
	HAL_UART_AbortReceive_IT(huart);
	rBuffer.fill(0);
	startReceive();
}
