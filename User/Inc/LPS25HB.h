#pragma once

using namespace std;

#include <cstdint>
#include <array>
#include <vector>

class LPS25HB {
 public:
  LPS25HB();

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

  bool begin(LPS25HB_Address SA0,
             LPS25HB_FIFO_MODE fifoMode = LPS25HB_FIFO_MODE::FIFO_MEAN_MODE_x32,
             LPS25HB_RATE rate = LPS25HB_RATE::F25Hz);
  float getPressure(void);
  float getTemplature(void);

  bool whoAreYou(void);
  bool reset(void);
  void setMode(LPS25HB_FIFO_MODE fifoMode, LPS25HB_RATE rate);
  void setOffset(float hPa);

  virtual void writeData(uint8_t reg, uint8_t data) = 0;
  virtual uint8_t readData(uint8_t reg) = 0;

 private:
  virtual void write(uint8_t reg, uint8_t *data) = 0;
  virtual std::vector<uint8_t> read(uint8_t reg, uint8_t len = 1) = 0;

  uint8_t address;
};

class LPS25HB_STM32_HAL: public LPS25HB{
public:
	void writeData(uint8_t reg, uint8_t data) override;
	uint8_t readData(uint8_t reg) override;

private:
	void write(uint8_t reg, uint8_t *data) override;
	std::vector<uint8_t> read(uint8_t reg, uint8_t len = 1) override;
};
