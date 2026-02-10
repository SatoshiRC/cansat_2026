#pragma once

using namespace std;

#include <cstdint>
#include <array>
#include <vector>

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

class LPS25HB {
 public:
  enum class LPS25HB_FIFO_MODE : uint8_t {
    BYPASS_MODE = 0x00,
    FIFO_MODE = 0x20,
    STREAM_MODE = 0x40,
    STREAM_TO_FIFO_MODE = 0x60,
    BYPASS_TO_STREAM_MODE = 0x80,
    FIFO_MEAN_MODE_x2 = 0xC1,
    FIFO_MEAN_MODE_x4 = 0xC3,
    FIFO_MEAN_MODE_x8 = 0xC7,
    FIFO_MEAN_MODE_x16 = 0xCF,
    FIFO_MEAN_MODE_x32 = 0xDF,
    BYPASS_TO_FIFO_MODE = 0xE0,
  };

  enum class LPS25HB_RATE : uint8_t {
    ONESHOT = 0x00,
    F1Hz = 0x10,
    F7Hz = 0x20,
    F12_5Hz = 0x30,
    F25Hz = 0x40,
  };

  enum class LPS25HB_Address{
	  Low = 0x5c,
	  High = 0x5d
  };

  LPS25HB(){};
  LPS25HB(LPS25HB_Address SA0):address(static_cast<uint8_t>(SA0)){}

  bool begin(LPS25HB_FIFO_MODE fifoMode = LPS25HB_FIFO_MODE::FIFO_MEAN_MODE_x32,
             LPS25HB_RATE rate = LPS25HB_RATE::F25Hz);
  float getPressure(void);
  float getTemplature(void);
  void updateRawData();

  bool whoAreYou(void);
  bool reset(void);
  void setMode(LPS25HB_FIFO_MODE fifoMode, LPS25HB_RATE rate);
  void setOffset(float hPa);

  virtual void writeData(uint8_t reg, uint8_t data) = 0;
  virtual uint8_t readData(uint8_t reg) = 0;

 protected:
  uint8_t address;

 private:
  virtual void write(uint8_t reg, uint8_t *data, uint8_t len = 1) = 0;
  virtual void read(uint8_t reg, uint8_t *data, uint8_t len = 1) = 0;
  virtual void delay(uint8_t ms) = 0;

  std::array<uint8_t, 5> rawDataBuffer;
};

#ifdef USE_HAL_DRIVER
#include "i2c.h"
class LPS25HB_STM32_HAL: public LPS25HB{
public:
  LPS25HB_STM32_HAL():hi2c(nullptr){};
  LPS25HB_STM32_HAL(I2C_HandleTypeDef *hi2c, LPS25HB_Address SA0):LPS25HB(SA0), hi2c(hi2c){};
	void writeData(uint8_t reg, uint8_t data) override;
	uint8_t readData(uint8_t reg) override;

private:
  I2C_HandleTypeDef *hi2c;
	void write(uint8_t reg, uint8_t *data, uint8_t len = 1) override;
	void read(uint8_t reg, uint8_t *data, uint8_t len = 1) override;
  void delay(uint8_t ms);
};
#endif /* USE_HAL_DRIVER */
