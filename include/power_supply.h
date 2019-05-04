#ifndef POWER_SUPPLY_H
#define POWER_SUPPLY_H

#include <Arduino.h>
#include <Adafruit_INA219.h>
#include "comm.pb.h"


class PowerSupply {
private:
  uint32_t enablePin;
  uint8_t railNumber;
  int timeout = -1;
  int currentLimit = -1;
  int expectedVoltage = -1;

  long lastOnTime = -1;
  PowerState lastState = PowerState_OFF;

public:

    PowerSupply() = default;
  PowerSupply(uint32_t enablePin, uint8_t railNumber, int timeout, int currentLimit,
              int expectedVoltage);

  void power(bool state);
  virtual float getCurrent() = 0;
  virtual float getVoltage() = 0;
  PowerRailInfo getRailInfo();
  bool isCurrentOK();
  bool isVoltageOK();

  bool hasExpired();

  virtual void check();
  virtual void update() = 0;


};

struct INA219Cal {
    uint16_t calValue;
    uint32_t currentLSB;
    float powerLSB;
    uint16_t config;

    void print() {
        Serial.print("INA219Cal {\n calValue: ");
        Serial.print(calValue);
        Serial.print("\n currentLSB: ");
        Serial.print(currentLSB); 
        Serial.print("\n powerLSB: "); 
        Serial.print(powerLSB);
        Serial.print("\n config: ");
        Serial.print(config);
        Serial.println("\n}");
    }
};


class INA219Supply : public PowerSupply {
    Adafruit_INA219 ina219;
    uint8_t address = 0;

    float cVoltage = 0 ;
    float cAmps = 0;
    float cWatt = 0;

public:
    INA219Supply() = default;
    INA219Supply(INA219Cal cal, uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage,
                 uint8_t address, uint8_t railNumber);

    static INA219Cal defaultCalibration();

    float getCurrent() override;

    float getVoltage() override;

    void update() override;

};


class LowRSunt219 : public INA219Supply {

public:
    LowRSunt219(uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage, uint8_t address);

    virtual INA219Cal getCalibration();
};

INA219Cal calculateCalibration(float currentRange, float shuntR);
INA219Cal calculateCorrection(INA219Cal in, int ina219Measured, int actualMeasured);

#endif