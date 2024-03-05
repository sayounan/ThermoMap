cmake_minimum_required(VERSION 3.27)
project(ThermoMap C)

set(CMAKE_C_STANDARD 11)

include_directories(C++)

add_executable(ThermoMap
        C++/AS6221.c
        C++/AS6221.h
        C++/tmp102.h
        C++/tmp102.cpp
        C++/smbus.cpp
        C++/smbus.h)
