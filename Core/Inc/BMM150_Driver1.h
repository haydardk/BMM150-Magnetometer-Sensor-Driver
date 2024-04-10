/*
 * BMM150_Driver1.h
 *
 *  Created on: Apr 10, 2024
 *      Author: CASPER
 */

#ifndef INC_BMM150_DRIVER1_H_
#define INC_BMM150_DRIVER1_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"

//Protocol select 0-1 for SPI-I2C

#define CHIP_ID 0x40 //0x32
#define X_LSB 0x42 // bit 3-7  >> x , 0-4
#define X_MSB 0x43 // all bits >> x, 5-12
#define Y_LSB 0x44 // same as X
#define Y_MSB 0x45
#define Z_LSB 0x46  // bit 1-7 >> z 0-6
#define Z_MSB 0x47  // all bits >> z 7-14

#define DataReady 0x4E

#define I2C_ADDR (0x10<<1)
#define WAKEUP 0X4C // default 0x06 opmode bit 1-2 >>>> 0x00
#define POWER 0x4B // 0x01  >>  >> 0x01

int WhoAmI(void);
int WakeUp(void);
void Get_DataReady(void);
void Process_Data(uint16_t *magx ,uint16_t *magy ,uint16_t *magz);

#endif /* INC_BMM150_DRIVER1_H_ */
