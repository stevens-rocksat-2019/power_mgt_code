
#include <power_supply.h>
#include "pins.h"

long getCurrentTime() {
    return millis();
}

INA219Supply::INA219Supply(uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage, uint8_t address)
        : PowerSupply(
        enablePin, timeout, currentLimit, expectedVoltage), address(address) {
    ina219 = Adafruit_INA219(address);
    ina219.begin();
}

float INA219Supply::getCurrent() {
    return cAmps;
}

float INA219Supply::getVoltage() {
    return cVoltage;
}


void INA219Supply::check() {
    update();
    PowerSupply::check();
}

void INA219Supply::update() {
    cVoltage = ina219.getBusVoltage_V();
    cAmps = ina219.getCurrent_mA();
    cWatt = ina219.getPower_mW();
}

PowerSupply::PowerSupply(uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage) :
    enablePin(enablePin), timeout(timeout), currentLimit(currentLimit), expectedVoltage(expectedVoltage) { }

void PowerSupply::power(bool state) {
    digitalWrite(enablePin, state);
}

bool PowerSupply::hasExpired() {
    return (getCurrentTime() > lastOnTime);
}

void PowerSupply::check() {
    if (hasExpired() || !isCurrentOK() || isVoltageOK()) {
        power(false);
    }
}

bool PowerSupply::isCurrentOK() {
    return getCurrent() < currentLimit;
}

bool PowerSupply::isVoltageOK() {
    return getVoltage() > expectedVoltage;
}


