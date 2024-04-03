/*
Created by Sari I. Younan
05/03/2024 10:04:57
tmp102.h
*/

#ifndef THERMOMAP_TMP102_H
#define THERMOMAP_TMP102_H

#include <bitset>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#define PORT 8080

using namespace std;

class TMP102 {
private:
    int file_i2c;
    int addr;
    int len;
    unsigned char buffer[60];

    void readConfig();
    void writeConfig();

public:
    TMP102 (const char *filename, int address);
    ~TMP102();
    void initialize();
    void setSampRate(int rate);
    float readTemp();

};
#endif //THERMOMAP_TMP102_H
