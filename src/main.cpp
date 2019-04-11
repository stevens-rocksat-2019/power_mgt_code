#include "pins.h"
#include "power_supply.h"
#include <Arduino.h>

INA219Supply *supplies;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  supplies = new INA219Supply[6];

  while (!Serial) {
    ;
  }
  for (int i = 0; i < 6; i++) {
    Serial.print("Initilizing supply ");
    Serial.println(i);
    supplies[i] = INA219Supply(EN_PINS[i], 10000, 1, 1, I2C_ADDRESSES[i]);
    Serial.print("Finished #");
    Serial.println(i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:


  Serial.print("Voltage: ");
  Serial.println(supplies[0].getVoltage());

  delay(1000);
}
