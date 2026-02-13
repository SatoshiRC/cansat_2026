#include "LPS25HB.h"

constexpr uint16_t timeout = 500;
constexpr uint16_t confirming_interval = 5;
constexpr uint16_t confirming_max_count = (timeout / confirming_interval);

bool LPS25HB::reset(void) {
  // ソフトウェアリセット
  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2), 0x04);
  // リセット確認
  for (uint16_t i = 0; i < confirming_max_count; i++) {
    if (readData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2)) == 0) { break; }
    if (i == (confirming_max_count - 1)) { return false; }
    delay(5);
  }

  // リブートメモリ
  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2), 0x80);
  // リブート確認
  for (uint16_t i = 0; i < confirming_max_count; i++) {
    if (readData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2)) == 0) { break; }
    if (i == (confirming_max_count - 1)) { return false; }
    delay(5);
  }

  return true;
}

void LPS25HB::setMode(LPS25HB_FIFO_MODE fifoMode, LPS25HB_RATE rate) {
  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG1), 0x82 | static_cast<uint8_t>(rate));
  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2), 0x40);
  writeData(static_cast<uint8_t>(LPS25HB_REG::FIFO_CTRL), static_cast<uint8_t>(fifoMode));
}

bool LPS25HB::begin(LPS25HB_FIFO_MODE fifoMode, LPS25HB_RATE rate) {

  // デバイス応答確認
  if (!whoAreYou()) { return false; }

  // リセットと確認
  if (!reset()) { return false; }

  setMode(fifoMode, rate);
  return true;
}

bool LPS25HB::whoAreYou(void) {
  return (readData(static_cast<uint8_t>(LPS25HB_REG::WHO_AM_I)) == 0xBD);
}

float LPS25HB::getPressure(void) {
	std::vector data(rawDataBuffer.begin(), rawDataBuffer.begin()+3);
	uint32_t ldata = static_cast<uint32_t>(data[2]);
	ldata = (ldata << 8) | static_cast<uint32_t>(data[1]);
	ldata = (ldata << 8) | static_cast<uint32_t>(data[0]);
	return static_cast<float>(ldata) / 4096.0f;
}

float LPS25HB::getTemplature(void) {
	std::vector data(rawDataBuffer.begin()+3, rawDataBuffer.end());
	int16_t idata = static_cast<uint16_t>(data[1]);
	idata = (idata << 8) | static_cast<uint16_t>(data[0]);
	return 42.5 + static_cast<float>(idata) / 480.0f;
}

void LPS25HB::updateRawData(){
	read(static_cast<uint8_t>(LPS25HB_REG::PRESS_OUT_XL), rawDataBuffer.data(), 5);
}

void LPS25HB::setOffset(float offset_hPa) {
	uint32_t ldata = static_cast<uint32_t>(offset_hPa * 4096);
	writeData(static_cast<uint8_t>(LPS25HB_REG::RPDS_L), static_cast<uint8_t>((ldata >> 8) & 0xFF));
	writeData(static_cast<uint8_t>(LPS25HB_REG::RPDS_H), static_cast<uint8_t>((ldata >> 16) & 0xFF));
}

//void LPS25HB::writeData(uint8_t reg, uint8_t data) {
//  wire->beginTransmission(address);
//  wire->write(reg);
//  wire->write(data);
//  wire->endTransmission();
//}
//
//uint8_t LPS25HB::readData(uint8_t reg) {
//  wire->beginTransmission(address);
//  wire->write(reg);
//  wire->endTransmission(false);
//  wire->requestFrom(address, (uint8_t)1);
//  return wire->read();
//}

void LPS25HB_STM32_HAL::writeData(uint8_t reg, uint8_t data){
	HAL_I2C_Mem_Write(hi2c, address<<1, reg, 1, &data, 1, 10);
}

uint8_t LPS25HB_STM32_HAL::readData(uint8_t reg){
  uint8_t res = 0;
  HAL_I2C_Mem_Read(hi2c, address<<1, reg, 1, &res, 1, 10);
  return res;
}

void LPS25HB_STM32_HAL::write(uint8_t reg, uint8_t *data, uint8_t len){
	reg |= 0b1<<7;
	HAL_I2C_Mem_Write_DMA(hi2c, address<<1, reg, 1, data, len);
}
void LPS25HB_STM32_HAL::read(uint8_t reg, uint8_t *data, uint8_t len){
	reg |= 0b1<<7;
	HAL_I2C_Mem_Read_DMA(hi2c, address<<1, reg, 1, data, len);
}

void LPS25HB_STM32_HAL::delay(uint8_t ms){
  HAL_Delay(ms);
}
