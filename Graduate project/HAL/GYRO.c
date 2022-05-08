/**
  ******************************************************************************
  * @file    GYRO.c
  * @author  Mostafa ElFallal
  * @date    02-March-2022
  ******************************************************************************
*/
#include "Gyroscope.h"

void GYRO_init(void){
  
  
#if  defined(A3G)
  uint8_t buf[] = {A3G_CTRL_REG1 , 0xFF};
  //max BW & data rate with enabling
  I2C_myTransmit(I2C2,A3G_I2C_ADDRESS,buf,2);
  buf[0] = A3G_CTRL_REG3;
  buf[0] = 0x10; //open drain
  I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
#elif defined(IAM)
  //don't need i think
#elif defined(MPU6050)
  uint8_t buf[] = {MPU6050_PWR_MGMT_1 , 0x80}; 
  I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
  buf[1] = 0x00;
  I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
  I2C_myRequest(I2C2,MPU6050_I2C_ADDRESS,MPU6050_PWR_MGMT_2,&buf[1],1);
  buf[1] &= ~(0x38 | 0x07);
  buf[0] = MPU6050_PWR_MGMT_2;
  I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
  buf[1] = ( 0x00 << 3 );
  buf[0] = MPU6050_ACCEL_CONFIG;
  I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
  buf[1] = ( 0x03 << 3 );
  buf[0] = MPU6050_GYRO_CONFIG;
  I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
#else
  //nothing
  
#endif
  
}
void GYRO_Read(float *data){
  uint8_t reader[6] = {0};
#if  defined(A3G)
  I2C_myRequest(I2C2,A3G_I2C_ADDRESS,A3G_OUT_X_L,reader,6);
  data[0] = (float)((int16_t)((reader[1]<< 8) | reader[0])) * 0.00875f;
  data[1] = (float)((int16_t)((reader[3]<< 8) | reader[2])) * 0.00875f;
  data[2] = (float)((int16_t)((reader[5]<< 8) | reader[4])) * 0.00875f;
#elif defined(IAM)
  I2C_myRequest(I2C2,IAM_I2C_ADDRESS,IAM_XOUT_H,reader,6);
  data[0] = (float)((int16_t)((reader[0]<< 8) | reader[1])) / 131f ;
  data[1] = (float)((int16_t)((reader[2]<< 8) | reader[3])) * 131f;
  data[2] = (float)((int16_t)((reader[4]<< 8) | reader[5])) * 131f;
#elif defined(MPU6050)
  
  I2C_myRequest(I2C2,MPU6050_I2C_ADDRESS,MPU6050_GYRO_XOUT_H,reader,6);
  data[0] = (float)((int16_t)((reader[0]<< 8) | reader[1])) * 0.001064225153455f;
  data[1] = (float)((int16_t)((reader[2]<< 8) | reader[3])) * 0.001064225153455f;
  data[2] = (float)((int16_t)((reader[4]<< 8) | reader[5])) * 0.001064225153455f;
#else
  data[0] = 50.6 + reader[0];
  data[1] = 60.5;
  data[2] = 70.4;
#endif
}
uint8_t GYRO_read_WIA(void){
  uint8_t reader;
#if  defined(A3G)
  I2C_myRequest(I2C2,A3G_I2C_ADDRESS,A3G_WHO_AM_I,&reader,1);
#elif defined(IAM)
  I2C_myRequest(I2C2,IAM_I2C_ADDRESS,IAM_WHO_AM_I,&reader,1);
#elif defined(MPU6050)
  
  I2C_myRequest(I2C2,MPU6050_I2C_ADDRESS,MPU6050_WHO_AM_I,&reader,1);
#else 
  reader = 0x55;
#endif
  return reader;
}