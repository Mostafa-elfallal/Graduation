/**
  ******************************************************************************
  * @file    Temp_STDS75.c
  * @author  Mostafa ElFallal
  * @date    13-Feb-2022
  ******************************************************************************
*/
/*
  ******************************************************************************
  * This is the temperature sensor Driver implementation file 
  ******************************************************************************
*/
#include "Temp_STDS75.h"
extern float Gyro_temp;
#if defined(USE_TEMP )
static TempSensor_t sensor = {
    .resBits = Res_12bits,
    .mode=Mode_Comparator ,
	.flt = Fault_1	
};
#endif
void Temp_init(void)
{
#if defined(USE_TEMP)
  uint8_t data[3];
  uint8_t val = 0x00;
  sensor.res = 0.125;
  sensor.shiftBits = 5;
  
  val = ( (uint8_t)sensor.resBits | (uint8_t)sensor.flt | (uint8_t)sensor.mode);
  data[0] = 0x1;    data[1] = 0x40; 
  // writing config byte
 I2C_myTransmit(I2C2,STDS75_ADDRESS,data,2);
#endif
}
//  TODO 
//  enable interrupt for sensor 
float Temp_Read(void)
{
#ifdef USE_TEMP
  uint8_t data[2] = {0};
  I2C_myRequest(I2C2 , STDS75_ADDRESS , 0 , data , 2);
  float temp = (((float)((data[0]<<8 | data[1])>>sensor.shiftBits))) * (sensor.res) ;
  return temp;
#elif defined(USE_TEMPMPU )
	return  Gyro_temp;
#else
  return 37.5;
#endif
}