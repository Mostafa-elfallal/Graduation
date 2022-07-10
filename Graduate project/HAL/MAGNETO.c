/**
  ******************************************************************************
  * @file    MAGNETO.c
  * @author  Mostafa ElFallal
  * @date    19-March-2022
  ******************************************************************************
*/
#include "main.h"
#include "magnetometer.h"

void MAGNETO_init(void)
{
#if  defined(LIS2)
  // 100 Hz and Continuous mode .
  uint8_t buf[] = {LIS2MDL_CFG_REG_A,LIS2MDL_RATE_100_HZ << 2}; 
  I2C_myTransmit(I2C2,LIS2MDL_ADDRESS_MAG,buf,2);
  //DRDY_on_PIN
  buf[0] = LIS2MDL_CFG_REG_C;
  buf[1] = 0x01;
  I2C_myTransmit(I2C2,LIS2MDL_ADDRESS_MAG,buf,2);
  
#elif defined(LIS3)
  uint8_t buf[] = {LIS3MDL_REG_CTRL_REG1,0x5E }; 
  I2C_myTransmit(I2C2,LIS3MDL_I2CADDR_DEFAULT,buf,2);
  //DRDY_on_PIN
  buf[0] = LIS3MDL_REG_CTRL_REG3;
  buf[1] = 0x00;
  I2C_myTransmit(I2C2,LIS3MDL_I2CADDR_DEFAULT,buf,2);
  buf[0] = LIS3MDL_REG_CTRL_REG4;
  buf[1] = 0x08;
  I2C_myTransmit(I2C2,LIS3MDL_I2CADDR_DEFAULT,buf,2);
#elif defined(USE_HMC)
  uint8_t buf[] = {HMC5883_CRA_REG_M,0xF0}; 
  I2C_myTransmit(I2C2,HMC5883_ADDRESS,buf,2);
  buf[0] = HMC5883_CRB_REG_M;
  buf[1] = 0x20;
  I2C_myTransmit(I2C2,HMC5883_ADDRESS,buf,2);
  buf[0] = HMC5883_MR_REG_M;
  buf[1] = 0x00;
  I2C_myTransmit(I2C2,HMC5883_ADDRESS,buf,2);
#else
  // do nothing 
#endif
}
void MAGNETO_Read(float *data)
{
  uint8_t reader[6] = {0};
  float scale;
#if  defined(LIS2)
  I2C_myRequest(I2C2,LIS2MDL_ADDRESS_MAG,LIS2MDL_OUTX_L_REG,reader,6);
  data[0] = (float)( reader[0] | (reader[1] << 8 ) ) * LIS2MDL_MAG_LSB *
    LIS2MDL_MILLIGAUSS_TO_MICROTESLA;
  data[1] = (float)( reader[2] | (reader[3] << 8) ) * LIS2MDL_MAG_LSB *
    LIS2MDL_MILLIGAUSS_TO_MICROTESLA;
  data[2] = (float)( reader[4] | (reader[5] << 8) ) * LIS2MDL_MAG_LSB *
    LIS2MDL_MILLIGAUSS_TO_MICROTESLA;
#elif defined(LIS3)
  I2C_myRequest(I2C2,LIS3MDL_I2CADDR_DEFAULT,LIS3MDL_REG_OUT_X_L,reader,6);
  scale = 1711; // change this when changing range
  data[0] = (float)( reader[0] | (reader[1] << 8 ) ) / scale * 100;
  data[1] = (float)( reader[2] | (reader[3] << 8) ) / scale * 100;
  data[2] = (float)( reader[4] | (reader[5] << 8) ) / scale * 100;
#elif defined(USE_HMC)
  I2C_myRequest(I2C2,HMC5883_ADDRESS,HMC5883_OUT_X_H_M,reader,6);
  scale = 1090.0; // change this when changing range
  data[0] = (int16_t)( reader[1] | (reader[0] << 8 ) ) / scale * 100.0;
  data[1] = (int16_t)( reader[3] | (reader[2] << 8) ) / scale * 100;
  data[2] = (int16_t)( reader[5] | (reader[4] << 8) ) / scale * 100;
#else
   scale = 0;
  data[0] = 3.2+reader[0]+scale;
  data[1] = 2.5;
  data[2] = 4.9;
#endif
  
}

uint8_t MAGNETO_read_WIA(void)
{
  uint8_t reader;
#if  defined(LIS2)
  I2C_myRequest(I2C2,LIS2MDL_ADDRESS_MAG,LIS2MDL_WHO_AM_I,&reader,1);
#elif defined(LIS3)
  I2C_myRequest(I2C2,LIS3MDL_I2CADDR_DEFAULT,LIS3MDL_REG_WHO_AM_I,&reader,1);
#elif defined(USE_HMC)
  I2C_myRequest(I2C2,HMC5883_ADDRESS,HMC5883_IRA_REG_M,&reader,1);
#else
  reader = 0xAA;
#endif
  
  return reader;
}
