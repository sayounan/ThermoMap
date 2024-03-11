/*
Created by Sari I. Younan
05/03/2024 10:04:57
tmp102.h
*/

#ifndef THERMOMAP_TMP102_H
#define THERMOMAP_TMP102_H

#include <bitset>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

using namespace std;

class TMP102 {
private:
    int file_i2c;
    int addr;
    unsigned char buffer[60];

    void readConfig();
    void writeConfig();
    int twosComp(int vals, int bits);

public:
    TMP102 (const char *filename, int address);
    ~TMP102();
    void initialize();
    void setSampRate(int rate);
    float readTemp();

};
#endif //THERMOMAP_TMP102_H
