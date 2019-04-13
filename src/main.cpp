#include "pins.h"
#include "power_supply.h"
#include <Arduino.h>

INA219Supply *supplies;

void displayVoltage();

#define num_supplies 6

void setAllPower(bool state) {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i].power(state);
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  supplies = new INA219Supply[num_supplies];

  while (!Serial) {
    ;
  }

  for (int i = 0; i < num_supplies; i++) {
    Serial.print("Initilizing supply ");
    Serial.println(i);
    supplies[i] = INA219Supply(EN_PINS[i], 10000, 1, 1, I2C_ADDRESSES[i]);
    Serial.print("Finished #");
    Serial.println(i);
  }

  pinMode(0, HIGH);
  pinMode(1, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
}

void displayCurrent() {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i].update();
    Serial.print("   ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(supplies[i].getCurrent());
  }
  Serial.println();
}
void displayVoltage() {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i].update();
    Serial.print("   ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(supplies[i].getVoltage());
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Voltage:");

  setAllPower(true);
  for (int i = 0; i < 10; i++) {
    displayVoltage();
    displayCurrent();
    Serial.println();
    delay(500);
  }

  setAllPower(false);
  for (int i = 0; i < 4; i++) {
    displayVoltage();
    displayCurrent();
    Serial.println();
    delay(500);
  }
}
