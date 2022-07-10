/**
  ******************************************************************************
  * @file    Temp_STDS75.h
  * @author  Mostafa ElFallal
  * @date    13-Feb-2022
  ******************************************************************************
*/
/*
  ******************************************************************************
  * This is the temperature sensor Driver include file 
  ******************************************************************************
*/
#ifndef __Temp_sens_H
#define __Temp_sens_H
#include "main.h"
#define MPU6050_I2C_ADDRESS 0x68
typedef enum {
    Res_9bits   = 0,  //150ms     // 0.5 C
    Res_10bits  = (1<<5), //300 ms     // 0.25 C
    Res_11bits  = (2<<5), // 600 ms   // 0.125 C
    Res_12bits  = (3<<5)// 1200 ms  // 0.0625 C
}Resolution_t;

//  (consecutive faults)

typedef enum {
    Fault_1 = 0,
    Fault_2 = (1<<3),
    Fault_4 = (2<<3),
    Fault_6 = (3<<3)
}Fault_t;

// mode 
typedef enum {
    Mode_Comparator = 0,
    Mode_Interrupt = 2
}Mode_t;

typedef struct {
    float res;
    float hys;
    float OT;
    Resolution_t resBits;
    Fault_t flt;
    Mode_t mode;
    uint8_t shiftBits;
}TempSensor_t;
void Temp_init(void);
//  TODO 
//  enable interrupt for sensor 
float Temp_Read(void);
#endif