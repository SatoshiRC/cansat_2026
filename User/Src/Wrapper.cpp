/*
 * Wrapper.cpp
 *
 *  Created on: Dec 22, 2025
 *      Author: OHYA Satoshi
 */

void init(){

}

void loop(){

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(huart == huartDebug){
		if(huart->RxEventType == HAL_UART_RXEVENT_IDLE){
		}
	}
}
