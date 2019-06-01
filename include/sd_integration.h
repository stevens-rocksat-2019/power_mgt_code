//
// Created by jesse on 5/27/19.
//

#ifndef POWER_MGT_CODE_SD_INTEGRATION_H
#define POWER_MGT_CODE_SD_INTEGRATION_H

#include <SD.h>
//#include "cobs.h"
// Set the pins used
#define cardSelect 4

File logfile;
bool SD_Ready = false;

// blink out an error code
void error(uint8_t errno) {
//    while(1) {
//        uint8_t i;
//        for (i=0; i<errno; i++) {
//            digitalWrite(13, HIGH);
//            delay(100);
//            digitalWrite(13, LOW);
//            delay(100);
//        }
//        for (i=errno; i<10; i++) {
//            delay(200);
//        }
//    }
}


void init_sd() {
//    pinMode(13, OUTPUT);


    // see if the card is present and can be initialized:
    if (!SD.begin(cardSelect)) {
//        Serial.println("Card init. failed!");
        error(2);
        SD_Ready = false;
        return;
    }
    char filename[15];
    strcpy(filename, "/ANALOG00.TXT");
    for (uint8_t i = 0; i < 100; i++) {

        filename[7] = '0' + i/10;
        filename[8] = '0' + i%10;
        // create if does not exist, do not open existing, write, sync after write
        if (! SD.exists(filename)) {
            break;
        }
    }

    logfile = SD.open(filename, FILE_WRITE);
    if( ! logfile ) {
//        Serial.print("Couldnt create ");
//        Serial.println(filename);
        error(3);
        SD_Ready = false;
        return;
    }
//    Serial.print("Writing to ");
//    Serial.println(filename);

//    pinMode(13, OUTPUT);
//    pinMode(8, OUTPUT);
//    Serial.println("Ready!");
    SD_Ready = true;
}

uint8_t encode_buffer[200];

void save_data(uint8_t *data, size_t count) {
    if (SD_Ready) {
        // COBS::encode(data, count, encode_buffer);
        encode_buffer[0] = ((uint16_t )count >> 8) & 0xFF;
        encode_buffer[1] = (uint16_t )count & 0xFF;
        for (int i = 0; i < count; i++){
            encode_buffer[i+2] = data[i];
        }
//        encode_buffer[count] = 0; // Set null delimiter for sending

        logfile.write(encode_buffer, count+2);
    }
    logfile.flush();
}


#endif //POWER_MGT_CODE_SD_INTEGRATION_H
