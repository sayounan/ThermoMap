/*
 * AS6221.c
 *
 *  Created on: Nov 15, 2021
 *      Author: angoosh
 */

#include <stdint.h>
#include "AS6221.h"
#include "main.h"

extern I2C_HandleTypeDef AS6221_I2C_HANDLE;

 /*
  * @brief Reads temperature measured by sensor
  * @retval temperature in C
  */
float AS6221_Read_Temperature(){
	uint8_t temp_raw[2];
	uint16_t temp_bin = 0;
	double temp = 0;
	uint8_t index[1] = {1};

	HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), index, 2, 0xFFFF);
	HAL_I2C_Master_Receive(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), temp_raw, 2, 0xFFFF);

	temp_bin = temp_raw[0] * 256 + temp_raw[1];

	if(temp_bin >= 0x8000){//is negative
		temp = ((~(temp_bin - 1)) * LSB) * (-1);
	}
	else{//is positive
		temp = temp_bin * LSB;
	}

	return temp;
}

/*
 * @brief Reads and Writes to control register
 * @param register
 * @param value to write
 * @param access operation: R,W,RW
 * @retval register contents
 */
int AS6221_Register(SETUP_REG reg, uint8_t value, ACCESS_OP rw){
	uint8_t conf_reg[2];
	uint8_t index[1] = {1};

	HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), index, 2, 0xFFFF);
	HAL_I2C_Master_Receive(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), conf_reg, 2, 0xFFFF);

	switch(reg){
	case AL:
		return ((conf_reg[0] & 0x04) >> 2);

	case CR:
		if(rw == R){
			return (conf_reg[0] & 0x03);
		}
		else if(rw == W){
			value = value & 0x03;
			conf_reg[0] = (conf_reg[0] & ~(0x03 << 0));
			conf_reg[0] = (conf_reg[0] | (value << 0));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);
		}
		else{
			value = value & 0x03;
			uint8_t retVal =(conf_reg[0] & 0x03);
			conf_reg[0] = (conf_reg[0] & ~(0x03 << 0));
			conf_reg[0] = (conf_reg[0] | (value << 0));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);

			return retVal;
		}
	case SM:
		if(rw == R){
			return (conf_reg[1] & 0x80);
		}
		else if(rw == W){
			value = value & 0x01;
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 7));
			conf_reg[1] = (conf_reg[1] | (value << 7));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);
		}
		else{
			value = value & 0x01;
			uint8_t retVal =(conf_reg[1] & 0x80);
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 7));
			conf_reg[1] = (conf_reg[1] | (value << 7));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);

			return retVal;
		}
	case IM:
		if(rw == R){
			return (conf_reg[1] & 0x40);
		}
		else if(rw == W){
			value = value & 0x01;
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 6));
			conf_reg[1] = (conf_reg[1] | (value << 6));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);
		}
		else{
			value = value & 0x01;
			uint8_t retVal =(conf_reg[1] & 0x40);
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 6));
			conf_reg[1] = (conf_reg[1] | (value << 6));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);

			return retVal;
		}
	case POL:
		if(rw == R){
			return (conf_reg[1] & 0x20);
		}
		else if(rw == W){
			value = value & 0x01;
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 5));
			conf_reg[1] = (conf_reg[1] | (value << 5));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);
		}
		else{
			value = value & 0x01;
			uint8_t retVal =(conf_reg[1] & 0x20);
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 5));
			conf_reg[1] = (conf_reg[1] | (value << 5));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);

			return retVal;
		}
	case CF:
		if(rw == R){
			return (conf_reg[1] & 0x18);
		}
		else if(rw == W){
			value = value & 0x03;
			conf_reg[1] = (conf_reg[1] & ~(0x03 << 3));
			conf_reg[1] = (conf_reg[1] | (value << 3));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);
		}
		else{
			value = value & 0x03;
			uint8_t retVal =(conf_reg[1] & 0x18);
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 3));
			conf_reg[1] = (conf_reg[1] | (value << 3));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);

			return retVal;
		}
	case SS:
		if(rw == R){
			return (conf_reg[1] & 0x01);
		}
		else if(rw == W){
			value = value & 0x01;
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 0));
			conf_reg[1] = (conf_reg[1] | (value << 0));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);
		}
		else{
			value = value & 0x01;
			uint8_t retVal =(conf_reg[1] & 0x01);
			conf_reg[1] = (conf_reg[1] & ~(0x01 << 0));
			conf_reg[1] = (conf_reg[1] | (value << 0));

			uint8_t msg[3] = {index[0], conf_reg[0], conf_reg[1]};
			HAL_I2C_Master_Transmit(&AS6221_I2C_HANDLE, (AS6221_ADDRESS << 1), msg, 4, 0xFFFF);

			return retVal;
		}
	}
	return 0;
}

