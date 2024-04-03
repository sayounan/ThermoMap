/*
Created by Sari I. Younan
05/03/2024 10:04:57
tmp102.cpp
*/

#include "tmp102.h"



TMP102::TMP102(const char *filename, int address) : addr(address), len(), buffer(){
    if ((file_i2c = open(filename, O_RDWR)) < 0) {
        cerr << "Failed to open the i2c bus" << endl;
        throw runtime_error("Failed to open the i2c bus");
    }

    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0) {
        cerr << "Failed to access bus or communicate with remote." << endl;
        throw runtime_error("Failed to access bus or communicate with remote.");
    }
}

TMP102::~TMP102() {
    close(file_i2c);
}

void TMP102::initialize() {
    readConfig();
    setSampRate(4);  // Initializes sampling rate at 4 Hz (CR1, CR0 = 0b10)
    writeConfig();
    readConfig();  // Simply verifies that the previous line actually changed the config
}

void TMP102::setSampRate(int rate) {
    readConfig();
    buffer[1] &= 0b00111111;
    buffer[1] |= (rate << 6);
}

float TMP102::readTemp() {
    buffer[0] = 0x00;
    len = 1;
    if (write(file_i2c, buffer, len) != len) {
        cerr << "Failed to write/configure i2c bus." << endl;
    }
    len = 2;
    if (read(file_i2c, buffer, len) != len) {
        cerr << "Failed to read from i2c bus." << endl;
    }

    int tempC = ((buffer[0] << 4) | (buffer[1] >> 4));
    if (tempC > 2047) {
        tempC -= 4096;
    }
    return static_cast<float>(tempC * 0.0625);
}

void TMP102::readConfig() {
    buffer[0] = 0x01;
    len = 1;
    if (write(file_i2c, buffer, len) != len) {
        cerr << "Failed to write/configure i2c bus." << endl;
    }
    len = 2;
    if (read(file_i2c, buffer, len) != len) {
        cerr << "Failed to read from i2c bus." << endl;
    }
}

void TMP102::writeConfig() {
    if (write(file_i2c, buffer, len) != len) {
         cerr << "Failed to write/configure i2c bus." << endl;
    }
}

volatile sig_atomic_t running = true;

void signalHandle(int sig) {
    if (sig == SIGINT) {
        running = false;
    }
}

int main() {
    const char *filename = "/dev/i2c-1";
    int address = 0x48;  // TMP address on I2C bus

    signal(SIGINT, signalHandle);

    TMP102 tmp102(filename, address);
    tmp102.initialize();

    while (running) {
        float temp = tmp102.readTemp();
        cout << temp << "˚C" <<endl;
        this_thread::sleep_for(chrono::milliseconds(250));

    }

    return 0;

}
