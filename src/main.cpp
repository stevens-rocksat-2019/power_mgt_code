#include "pins.h"
#include "power_supply.h"
#include <Arduino.h>
#include <PacketSerial.h>
#include "comm.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "sd_integration.h"

#define num_supplies 6

PowerSupply *supplies[6];
PacketSerial packetSerial;

void displayVoltage();

void setAllPower(bool state) {
  for (int i = 0; i < num_supplies; i++) {
    supplies[i]->power(state);
  }
}


void onPacketReceived(const uint8_t* buffer, size_t size) {
    RxMicro rx = RxMicro_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(buffer, size);
    bool status = pb_decode(&stream, RxMicro_fields, &rx);
    if (status) {
        if(rx.has_powerControl && rx.powerControl.has_powerRail && rx.powerControl.has_powerState) {
            int rail = rx.powerControl.powerRail;
            if (rail != 0) {
                supplies[rail-1]->power(rx.powerControl.powerState);
            } else {
                setAllPower(rx.powerControl.powerState);
            }
        }
    }
}


void setup() {
  // put your setup code here, to run once:

  packetSerial.begin(115200);
  packetSerial.setPacketHandler(&onPacketReceived);
  while (!Serial) {
    ;
  }

  init_sd();

  supplies[0] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[0], 10000, 1, 1, I2C_ADDRESSES[0], 1);
  supplies[1] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[1], 10000, 1, 1, I2C_ADDRESSES[1], 2);
  supplies[2] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[2], 10000, 1, 1, I2C_ADDRESSES[2], 3);
  supplies[3] = new INA219Supply(calculateCorrection(calculateCalibration(10, 0.01), 10758, 8070), EN_PINS[3], 10000, 1,
                                 1, I2C_ADDRESSES[3], 4);
  supplies[4] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[4], 10000, 1, 1, I2C_ADDRESSES[4], 5);
  supplies[5] = new INA219Supply(INA219Supply::defaultCalibration(), EN_PINS[5], 10000, 1, 1, I2C_ADDRESSES[5], 6);

  pinMode(0, HIGH);
  pinMode(1, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  setAllPower(false);
}

uint8_t send_buffer[100];

void sendData() {
    TxMicro tx = TxMicro_init_zero;
    tx.powerRailInfo_count = num_supplies;
    for (int i = 0; i < num_supplies; i++) {
        supplies[i]->update();
        tx.powerRailInfo[i] = supplies[i]->getRailInfo();
    }

    pb_ostream_t stream = pb_ostream_from_buffer(send_buffer, sizeof(send_buffer));
    pb_encode(&stream, TxMicro_fields, &tx);

    if (Serial) {
        packetSerial.send(send_buffer, stream.bytes_written);
        packetSerial.update();
    }

    save_data(send_buffer, stream.bytes_written);
}

void loop() {
  // put your main code here, to run repeatedly:

  sendData();
  packetSerial.update();
}
