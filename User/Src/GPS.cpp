/*
 * GPS.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satosih
 */

#include <GPS.h>

GPS::GPS(State *state = new State, NMEAProcessor *nmeaProcessor = new NMEAProcessor, UART_HandleTypeDef *huart = &huart2)
:state(state), nmeaProcessor(nmeaProcessor), huart(huart){

}

void GPS::startReceive(){
	HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t*)rBuffer.data(), rBuffer.size());
}

void GPS::onReceive(){
	uint16_t rxCount = huart->RxXferCount;
	std::vector<uint8_t> rMessage(rxCount, rBuffer);
	nmeaProcessor->onReceive(rMessage);
}
