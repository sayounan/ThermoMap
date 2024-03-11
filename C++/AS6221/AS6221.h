/*
 * AS6221.h
 *
 *  Created on: Nov 15, 2021
 *      Author: angoosh
 */

#ifndef INC_AS6221_H_
#define INC_AS6221_H_

#include "stm32l0xx_hal.h"

#define AS6221_ADDRESS		0x48
#define LSB					(double)0.0078125

typedef enum {
	AL = 0,
	CR = 1,
	SM = 2,
	IM = 3,
	POL = 4,
	CF = 5,
	SS = 6
} SETUP_REG;

typedef enum {
	R = 0,
	W = 1,
	RW = 2
} ACCESS_OP;


float AS6221_Read_Temperature();
int AS6221_Register(SETUP_REG reg, uint8_t value, ACCESS_OP rw);

#endif /* INC_AS6221_H_ */
