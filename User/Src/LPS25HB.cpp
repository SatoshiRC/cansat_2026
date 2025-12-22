#include "LPS25HB.h"

enum class LPS25HB_REG : uint8_t {
  REF_P_XL = 0x08,
  REF_P_L = 0x09,
  REF_P_H = 0x0A,
  WHO_AM_I = 0x0F,
  RES_CONF = 0x10,
  CTRL_REG1 = 0x20,
  CTRL_REG2 = 0x21,
  CTRL_REG3 = 0x22,
  CTRL_REG4 = 0x23,
  INTERRUPT_CFG = 0x24,
  INT_SOURCE = 0x25,
  STATUS_REG = 0x27,
  PRESS_OUT_XL = 0x28,
  PRESS_OUT_L = 0x29,
  PRESS_OUT_H = 0x2A,
  TEMP_OUT_L = 0x2B,
  TEMP_OUT_H = 0x2C,
  FIFO_CTRL = 0x2E,
  FIFO_STATUS = 0x2F,
  THS_P_L = 0x30,
  THS_P_H = 0x31,
  RPDS_L = 0x39,
  RPDS_H = 0x3A,
};

constexpr uint16_t timeout = 500;
constexpr uint16_t confirming_interval = 5;
constexpr uint16_t confirming_max_count = (timeout / confirming_interval);

LPS25HB::LPS25HB() {}

bool LPS25HB::reset(void) {
//  // ソフトウェアリセット
//  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2), 0x04);
//  // リセット確認
//  for (uint16_t i = 0; i < confirming_max_count; i++) {
//    if (readData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2)) == 0) { break; }
//    if (i == (confirming_max_count - 1)) { return false; }
//    delay(5);
//  }
//
//  // リブートメモリ
//  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2), 0x80);
//  // リブート確認
//  for (uint16_t i = 0; i < confirming_max_count; i++) {
//    if (readData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2)) == 0) { break; }
//    if (i == (confirming_max_count - 1)) { return false; }
//    delay(5);
//  }
//
//  return true;
}

void LPS25HB::setMode(LPS25HB_FIFO_MODE fifoMode, LPS25HB_RATE rate) {
  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG1), 0x82 | static_cast<uint8_t>(rate));
  writeData(static_cast<uint8_t>(LPS25HB_REG::CTRL_REG2), 0x40);
  writeData(static_cast<uint8_t>(LPS25HB_REG::FIFO_CTRL), static_cast<uint8_t>(fifoMode));
}

bool LPS25HB::begin(LPS25HB_Address SA0, LPS25HB_FIFO_MODE fifoMode, LPS25HB_RATE rate) {
  address = (uint8_t)SA0;

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
  uint32_t ldata = static_cast<uint32_t>(readData(static_cast<uint8_t>(LPS25HB_REG::PRESS_OUT_H)));
  ldata = (ldata << 8) | static_cast<uint32_t>(readData(static_cast<uint8_t>(LPS25HB_REG::PRESS_OUT_L)));
  ldata = (ldata << 8) | static_cast<uint32_t>(readData(static_cast<uint8_t>(LPS25HB_REG::PRESS_OUT_XL)));
  return static_cast<float>(ldata) / 4096.0f;
}

float LPS25HB::getTemplature(void) {
  int16_t idata = static_cast<uint16_t>(readData(static_cast<uint8_t>(LPS25HB_REG::TEMP_OUT_H)));
  idata = (idata << 8) | static_cast<uint16_t>(readData(static_cast<uint8_t>(LPS25HB_REG::TEMP_OUT_L)));
  return 42.5 + static_cast<float>(idata) / 480.0f;
}

void LPS25HB::setOffset(float offset_hPa) {
  uint32_t ldata = static_cast<uint32_t>(offset_hPa * 4096);
  writeData(static_cast<uint8_t>(LPS25HB_REG::RPDS_L), static_cast<uint8_t>((ldata >> 8) & 0xFF));
  writeData(static_cast<uint8_t>(LPS25HB_REG::RPDS_H), static_cast<uint8_t>((ldata >> 16) & 0xFF));
}

void LPS25HB::writeData(uint8_t reg, uint8_t data) {
  wire->beginTransmission(address);
  wire->write(reg);
  wire->write(data);
  wire->endTransmission();
}

uint8_t LPS25HB::readData(uint8_t reg) {
  wire->beginTransmission(address);
  wire->write(reg);
  wire->endTransmission(false);
  wire->requestFrom(address, (uint8_t)1);
  return wire->read();
}
