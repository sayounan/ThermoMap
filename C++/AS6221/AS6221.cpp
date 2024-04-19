/*
Created by Sari I. Younan
05/03/2024 10:04:57
tmp102.cpp
*/

#include "AS6221.h"


AS6221::AS6221(const char *filename, int address) : addr(address), len(), buffer(){
    if ((file_i2c = open(filename, O_RDWR)) < 0) {
        cerr << "Failed to open the i2c bus" << endl;
        throw runtime_error("Failed to open the i2c bus");
    }

    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0) {
        cerr << "Failed to access bus or communicate with remote." << endl;
        throw runtime_error("Failed to access bus or communicate with remote.");
    }
}

AS6221::~AS6221() {
    close(file_i2c);
}

void AS6221::initialize() {
    readConfig();
    setSampRate(4);  // Initializes sampling rate at 4 Hz (CR1, CR0 = 0b10)
    writeConfig();
    readConfig();  // Simply verifies that the previous line actually changed the config
}

void AS6221::setSampRate(int rate) {
    readConfig();
    buffer[1] &= 0b00111111;
    buffer[1] |= (rate << 6);
}

float AS6221::readTemp() const {
    uint8_t buff[2] = {0};
    int16_t tempRaw;

    // Request temperature data
    if (write(file_i2c, &buff[0], 1) != 1) {
        cerr << "Failed to write to i2c bus." << endl;
        return -1; // Return an error value
    }

    // Read temperature data
    if (read(file_i2c, &buff[0], 2) != 2) {
        cerr << "Failed to read from i2c bus." << endl;
        return -1; // Return an error value
    }

    // Combine the two bytes into a 16-bit signed integer
    tempRaw = static_cast<int16_t>((buff[0] << 8) | buff[1]);

    // Convert to temperature in degrees Celsius
    auto temperature = static_cast<float>(tempRaw * 0.0078125); // AS6221 has a resolution of 0.005 degrees Celsius

    return temperature;
}

void AS6221::readConfig() {
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

void AS6221::writeConfig() {
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

    // TMP address on I2C bus, server file descriptor, new socket, buffer
    int address = 0x48, serverFd, newSocket;
    struct sockaddr_in addr = {};
    int opt = 1;
    int addrlen = sizeof(addr);
    char buffer[1024] = {0};

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket initialization failed: Could not create socket file descriptor.");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        char setsockerr[250];
        snprintf(setsockerr, sizeof(setsockerr), \
        "Socket attachment failed: Could not attach socket to port: %d", PORT);
        perror(setsockerr);
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if(bind(serverFd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        char bindsockerr[250];
        snprintf(bindsockerr, sizeof(bindsockerr), \
        "Socket binding failed: Could not bind socket to port: %d", PORT);
        perror(bindsockerr);
        exit(EXIT_FAILURE);
    }

    if(listen(serverFd, 3) < 0) {
        perror("Listen failed: Could not listen on specified port. Check fd assignment.");
        exit(EXIT_FAILURE);
    }

    cout << "Waiting for client..." << endl;

    if((newSocket = accept(serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrlen)) < 0) {
        perror("Could not accept new socket assignment.");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signalHandle);

    AS6221 as6221(filename, address);
    as6221.initialize();

    printf("%s\n", buffer);
    system("ThermoMap GUI.exe");

    while (running) {
        float temp = as6221.readTemp();
        string tempStr = to_string(temp);
        send(newSocket, tempStr.c_str(), tempStr.length(), 0);
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    close(newSocket);
    close(serverFd);

    return 0;
}
