/*
 * BMM150_Driver1.c
 *
 *  Created on: Apr 10, 2024
 *      Author: CASPER
 */
#include "BMM150_Driver1.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1 ;

uint8_t xlsb,xmsb,ylsb,ymsb,zlsb,zmsb;
int8_t power = 0x01;
int8_t wakeup = 0x00;
int8_t check;

int WhoAmI(void){
	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, CHIP_ID, 1, &check, 1, 10);
	if( check == 0x32){
		return 1;
	}else{
		return -1;
	}
}

int WakeUp(void){
	HAL_I2C_Mem_Write(&hi2c1, I2C_ADDR, POWER, 1, &power, 1, 10);
	HAL_I2C_Mem_Write(&hi2c1, I2C_ADDR, WAKEUP, 1, &wakeup, 1, 10);
	HAL_Delay(5);
	if (HAL_I2C_GetState(&hi2c1)){
    	return 5;
    }else {
    	return 4;
    }
}

void Get_DataReady(void){
	int8_t set=0x80;
	HAL_I2C_Mem_Write(&hi2c1, I2C_ADDR, DataReady, 1, &set, 1, 10);
}
void Process_Data(uint16_t *magx ,uint16_t *magy ,uint16_t *magz){

	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, X_LSB, 1, &xlsb, 1, 10);
	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, X_MSB, 1, &xmsb, 1, 10);
	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, Y_LSB, 1, &ylsb, 1, 10);
	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, Y_MSB, 1, &ymsb, 1, 10);
	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, Z_LSB, 1, &zlsb, 1, 10);
	HAL_I2C_Mem_Read(&hi2c1, I2C_ADDR, Z_MSB, 1, &zmsb, 1, 10);

	uint8_t pro_xlsb = xlsb >> 3 ;
	*magx = ((uint16_t)xmsb<<5) | pro_xlsb ;

	uint8_t pro_ylsb = ylsb >> 3 ;
	*magy = ((uint16_t)ymsb<<5) | pro_ylsb ;

	uint8_t pro_zlsb = zlsb >> 2 ;
	*magz = ((uint16_t)zmsb<<6) | pro_zlsb ;

}

