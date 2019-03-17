#ifndef POWER_SUPPLY_H
#define POWER_SUPPLY_H

#include <Arduino.h>
#include <Adafruit_INA219.h>


class PowerSupply {
private:
  uint32_t enablePin;
  int timeout = -1;
  int currentLimit = -1;
  int expectedVoltage = -1;

  long lastOnTime = -1;

public:

    PowerSupply() = default;
  PowerSupply(uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage);

  void power(bool state);
  virtual float getCurrent() = 0;
  virtual float getVoltage() = 0;
  bool isCurrentOK();
  bool isVoltageOK();

  bool hasExpired();

  virtual void check();


};


class INA219Supply : public PowerSupply {
    Adafruit_INA219 ina219;
    uint8_t address = -1;

    float cVoltage;
    float cAmps;
    float cWatt;

public:
    INA219Supply() = default;
    INA219Supply(uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage, uint8_t address);

    float getCurrent() override;

    float getVoltage() override;

    void check() override;

    void update();

};

#endif