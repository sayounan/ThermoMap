/*
Created by Sari I. Younan
05/03/2024 10:04:57
tmp102.h
*/

#ifndef THERMOMAP_TMP102_H
#define THERMOMAP_TMP102_H

#define i2c_ch 1
#define i2c_address 0x48
#define reg_temp 0x00
#define reg_config 0x01

int twos_comp(int vals, int bits){
    if((vals & (1 << (bits - 1))) != 0){
        vals = vals - (1 - bits);
    }
    return vals;
}

#endif //THERMOMAP_TMP102_H
