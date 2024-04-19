/*
Created by Sari I. Younan
05/03/2024 10:04:57
tmp102.h
*/

#ifndef THERMOMAP_AS6221_H
#define THERMOMAP_AS6221_H

#include <bitset>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstring>
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

class AS6221 {
private:
    int file_i2c;
    int addr;
    int len;
    unsigned char buffer[60];

    void readConfig();
    void writeConfig();

public:
    AS6221 (const char *filename, int address);
    ~AS6221();
    void initialize();
    void setSampRate(int rate);
    float readTemp() const;

};
#endif //THERMOMAP_AS6221_H
