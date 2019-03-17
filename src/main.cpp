#include "pins.h"
#include "power_supply.h"
#include <Arduino.h>

INA219Supply *supplies;

void print_voltages() {
  for (int i = 0; i < 8; i++) {
    supplies[i].update();
    Serial.print(supplies[i].getVoltage());
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  supplies = new INA219Supply[8];

  // while (!Serial) {
  //   ;
  // }

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);

  for (int i = 0; i < 8; i++) {
    Serial.print("Initilizing supply ");
    Serial.println(i);
    supplies[i] = INA219Supply(EN_PINS[i], 10000, 1, 1, I2C_ADDRESSES[i]);
    Serial.print("Finished #");
    Serial.println(i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 8; i++) {
    supplies[i].power(true);
  }

  for (int i = 0; i < 5; i++) {
    Serial.print("Voltage on:  ");
    print_voltages();
    delay(1000);
  }

  for (int i = 0; i < 8; i++) {
    supplies[i].power(false);
  }

  for (int i = 0; i < 5; i++) {
    Serial.print("Voltage off: ");
    print_voltages();
    delay(1000);
  }
}
