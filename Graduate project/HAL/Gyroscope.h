/**
  ******************************************************************************
  * @file    Gyroscope.h
  * @author  Mostafa ElFallal
  * @date    02-March-2022
  ******************************************************************************
*/
#ifndef __GYRO_H
#define __GYRO_H
#include "main.h"

#if  defined(A3G)
#include "GYRO_A3G.h"
#elif defined(IAM)
#include "GYRO_IAM.h"
#elif defined(MPU6050)
#include "GYRO_MPU.h"
#else 
#error "Use #define MPU or IAM or A3G"
#endif
void GYRO_init(void);
void GYRO_Read(float *data);
uint8_t GYRO_read_WIA(void);

#endif