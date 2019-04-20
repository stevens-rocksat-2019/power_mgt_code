#include "pins.h"
#include "power_supply.h"
#include <Arduino.h>


#define num_supplies 6

PowerSupply *supplies[6];

void displayVoltage();

void setAllPower(bool state) {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i]->power(state);
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  while (!Serial) {
    ;
  }

  supplies[0] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[0], 10000, 1, 1, I2C_ADDRESSES[0]);
  supplies[1] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[1], 10000, 1, 1, I2C_ADDRESSES[1]);
  supplies[2] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[2], 10000, 1, 1, I2C_ADDRESSES[2]);
  supplies[3] = new INA219Supply(calculateCorrection(calculateCalibration(10, 0.01), 10758, 8070), EN_PINS[3], 10000, 1, 1, I2C_ADDRESSES[3]);
  supplies[4] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[4], 10000, 1, 1, I2C_ADDRESSES[4]);
  supplies[5] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[5], 10000, 1, 1, I2C_ADDRESSES[5]);

  pinMode(0, HIGH);
  pinMode(1, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
}

void displayCurrent() {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i]->update();
    Serial.print("   ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(supplies[i]->getCurrent());
  }
  Serial.println();
}
void displayVoltage() {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i]->update();
    Serial.print("   ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(supplies[i]->getVoltage());
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

   Serial.print("==== power on ====");

  setAllPower(true);
  for (int i = 0; i < 10; i++) {
    displayVoltage();
    displayCurrent();
    Serial.println();
    delay(500);
  }

  Serial.print("==== power off ====");

  setAllPower(false);
  for (int i = 0; i < 4; i++) {
    displayVoltage();
    displayCurrent();
    Serial.println();
    delay(500);
  }
}
