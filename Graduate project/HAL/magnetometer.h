/**
  ******************************************************************************
  * @file    magnetometer.h
  * @author  Mostafa ElFallal
  * @date    19-March-2022
  ******************************************************************************
*/
#ifndef __MAGNETO_H
#define __MAGNETO_H

#if  defined(LIS2)
#include "MAGNETO_LIS2.h"
#elif defined(LIS3)
#include "MAGNETO_LIS3.h"
#elif defined(NO_MAGNETO)

#else 
#error "Use #define LIS2 or LIS3 or NO_MAGNETO"
#endif
void MAGNETO_init(void);
void MAGNETO_Read(float *data);
uint8_t MAGNETO_read_WIA(void);

#endif