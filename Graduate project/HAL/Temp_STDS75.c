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

#if defined(USE_TEMP )
static TempSensor_t sensor = {
    .resBits = Res_12bits,
    .mode=Mode_Interrupt
};
#endif
void Temp_init(void)
{
#if defined(USE_TEMP)
  uint8_t data[3];
  uint8_t val = 0x00;
  switch(sensor.resBits)
  {
  case Res_9bits  :
    sensor.res = 0.5;
    sensor.shiftBits = 7;
    break;
  case Res_10bits :
    sensor.res = 0.25;
    sensor.shiftBits = 6;
    break;
  case Res_11bits :
    sensor.res = 0.125;
    sensor.shiftBits = 5;
    break;
  case Res_12bits :
    sensor.shiftBits = 4;
    sensor.res = 0.0625;
    break;
  default :
    sensor.res = 0.5;
    sensor.shiftBits = 7;
  }
  val = ( (uint8_t)sensor.resBits | (uint8_t)sensor.flt | (uint8_t)sensor.mode);
  data[0] = 0x1;    data[1] = val; 
  // writing config byte
  I2C_myTransmit(I2C2,STDS75_ADDRESS,data,2);
  // writing hys two bytes
  uint16_t Hysteresis = ((uint16_t)(sensor.hys / sensor.res)) << sensor.shiftBits ;
  data[0] = 0x02;   data[1] = Hysteresis >> 8;  data[2] = Hysteresis & 0xff;
  I2C_myTransmit(I2C2,STDS75_ADDRESS,data , 3);
  // writing OT two bytes
  uint16_t OverTemp = ((uint16_t)(sensor.OT / sensor.res)) << sensor.shiftBits ;
  data[0] = 0x03;   data[1] = OverTemp >> 8;  data[2] = OverTemp & 0xff;
  I2C_myTransmit(I2C2,STDS75_ADDRESS,data , 3);
 
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
	uint8_t data[2] = {0};
	I2C_myRequest(I2C2 , MPU6050_I2C_ADDRESS , MPU6050_TEMP_OUT_H , data , 2);
	float temp = ((float)(data[0]<<8 | data[1]))/340.00-147.0 ;
	return temp;
#else
  return 37.5;
#endif
}