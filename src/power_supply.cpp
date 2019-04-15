
#include <power_supply.h>
#include "pins.h"

long getCurrentTime() {
    return millis();
}

INA219Supply::INA219Supply(INA219Cal cal, uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage, uint8_t address)
        : PowerSupply(
        enablePin, timeout, currentLimit, expectedVoltage), address(address) {
    ina219 = Adafruit_INA219(address);
    ina219.begin();

    ina219.ina219_calValue = cal.calValue;
    ina219.ina219_currentDivider_mA = cal.currentLSB;
    ina219.ina219_powerMultiplier_mW = cal.powerLSB;
    ina219.setCalibrationCurrent(cal.config);

}

float INA219Supply::getCurrent() {
    return cAmps;
}

float INA219Supply::getVoltage() {
    return cVoltage;
}


void INA219Supply::update() {
    cVoltage = ina219.getBusVoltage_V();
    cAmps = ina219.getCurrent_mA();
    cWatt = ina219.getPower_mW();
}

INA219Cal INA219Supply::defaultCalibration() {

    // same as: setCalibration_32V_2A

    struct INA219Cal retVal{};
    retVal.calValue = 4096;
    retVal.currentLSB = 10;
    retVal.powerLSB = 2;
    retVal.config = INA219_CONFIG_BVOLTAGERANGE_32V | // NOLINT(bugprone-suspicious-enum-usage)
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
    return retVal;
}

PowerSupply::PowerSupply(uint32_t enablePin, int timeout, int currentLimit, int expectedVoltage) :
    enablePin(enablePin), timeout(timeout), currentLimit(currentLimit), expectedVoltage(expectedVoltage) {
    pinMode(enablePin, OUTPUT);
}

void PowerSupply::power(bool state) {
    digitalWrite(enablePin, state);
}

bool PowerSupply::hasExpired() {
    return (getCurrentTime() > lastOnTime);
}

void PowerSupply::check() {
    update();
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

INA219Cal calculateCalibration(float currentRange, float shuntR) {
    Serial.print("calculateCalibration(");
    Serial.print(currentRange);
    Serial.print(", ");
    Serial.print(shuntR);
    Serial.println(")");

    struct INA219Cal retVal{};
    double current_lsb = (double)currentRange / (double)pow(2, 15);
    double cal = (double)0.0496 / (current_lsb * (double)shuntR);
    retVal.calValue = (uint16_t) cal;
    retVal.currentLSB = (uint32_t) (1/(1000*current_lsb));
    retVal.powerLSB = retVal.currentLSB * 20;

    retVal.config = INA219_CONFIG_BVOLTAGERANGE_16V | INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_SADCRES_12BIT_1S_532US | INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS; // NOLINT(bugprone-suspicious-enum-usage)

    float max_shunt_v = currentRange * shuntR * 1000;
    if (max_shunt_v < 40) {
        retVal.config |= INA219_CONFIG_GAIN_1_40MV;
    } else if (max_shunt_v < 80) {
        retVal.config |= INA219_CONFIG_GAIN_2_80MV;
    } else if (max_shunt_v < 160) {
        retVal.config |= INA219_CONFIG_GAIN_4_160MV;
    } else {
        retVal.config |= INA219_CONFIG_GAIN_8_320MV;
    }

    return retVal;
}

INA219Cal calculateCorrection(INA219Cal in, int ina219Measured, int actualMeasured){
    in.calValue = in.calValue * actualMeasured / ina219Measured;
    return in;
}


INA219Cal LowRSunt219::getCalibration() {
    Serial.println("calling correct calibration routine");
    return calculateCalibration(10, 0.01);
}
