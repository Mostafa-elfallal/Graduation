/**
  ******************************************************************************
  * @file    GYRO.c
  * @author  Mostafa ElFallal
  * @date    02-March-2022
  ******************************************************************************
*/
#include "Gyroscope.h"
#include "math.h"
#if  defined(A3G)
float test[3]={0};
void GYRO_test(void)
{
	uint8_t reader[6] = {0};
	for(int i =0;i<32;i++){
		I2C_myRequest(I2C2,A3G_I2C_ADDRESS,A3G_OUT_X_L|0x80,reader,6);
		test[0] += (float)((int16_t)((reader[1]<< 8) | reader[0])) * 0.00875f;
		test[1] += (float)((int16_t)((reader[3]<< 8) | reader[2])) * 0.00875f;
		test[2] += (float)((int16_t)((reader[5]<< 8) | reader[4])) * 0.00875f;
	}
	test[0]/=32;
	test[1]/=32;
	test[2]/=32;
}
#endif
#if  defined(MPU6050)
float  gyroXoffset ,gyroYoffset,gyroZoffset ,accXoffset ,accYoffset,accZoffset;
float filterGyroCoef ;
float  accX, accY, accZ, gyroX,  gyroY , gyroZ;
float Gyro_temp;
float  angleX , angleY ,  angleZ ;
float angleAccX,angleAccY;
static float wrap(float angle,float limit){
  while (angle >  limit) angle -= 2*limit;
  while (angle < -limit) angle += 2*limit;
  return angle;
}
void setGyroOffsets(float x, float y, float z){
  gyroXoffset = x;
  gyroYoffset = y;
  gyroZoffset = z;
}
void setAccOffsets(float x, float y, float z){
  accXoffset = x;
  accYoffset = y;
  accZoffset = z;
}
void setFilterGyroCoef(float gyro_coeff){
	if ((gyro_coeff<0) || (gyro_coeff>1)){ gyro_coeff = MPU66050_DEFAULT_GYRO_COEFF; } // prevent bad gyro coeff, should throw an error...
  filterGyroCoef = gyro_coeff;
}
void setFilterAccCoef(float acc_coeff){
  setFilterGyroCoef(1.0-acc_coeff);
}
void fetchData(){
  uint8_t reader[14];
  I2C_myRequest(I2C2,MPU6050_I2C_ADDRESS,MPU6050_ACCEL_XOUT_H,reader,14);
  int16_t rawData[7]; // [ax,ay,az,temp,gx,gy,gz]

  for(int i=0;i<7;i++){
	rawData[i]  = reader[i*2] << 8;
    rawData[i] |= reader[i*2 +1] ;
  }

  accX = ((float)rawData[0]) / MPU6050_acc_lsb_to_g - accXoffset;
  accY = ((float)rawData[1]) / MPU6050_acc_lsb_to_g - accYoffset;
  accZ = ((float)rawData[2]) / MPU6050_acc_lsb_to_g - accZoffset;
  Gyro_temp = (rawData[3] + 12412.0) / 340.0 ;
  gyroX = ((float)rawData[4]) / MPU6050_gyro_lsb_to_degsec - gyroXoffset;
  gyroY = ((float)rawData[5]) / MPU6050_gyro_lsb_to_degsec - gyroYoffset;
  gyroZ = ((float)rawData[6]) / MPU6050_gyro_lsb_to_degsec - gyroZoffset;
}
void calcOffsets(){
   setGyroOffsets(0,0,0); 
  setAccOffsets(0,0,0);
  float ag[6] = {0,0,0,0,0,0}; // 3*acc, 3*gyro
  
  for(int i = 0; i < MPU66050_CALIB_OFFSET_NB_MES; i++){
    fetchData();
	ag[0] += accX;
	ag[1] += accY;
	ag[2] += (accZ-1.0);
	ag[3] += gyroX;
	ag[4] += gyroY;
	ag[5] += gyroZ;
	for(uint32_t i=0;i<50000;i++)
		;
  }
    accXoffset = ag[0] / MPU66050_CALIB_OFFSET_NB_MES;
    accYoffset = ag[1] / MPU66050_CALIB_OFFSET_NB_MES;
    accZoffset = ag[2] / MPU66050_CALIB_OFFSET_NB_MES;
    gyroXoffset = ag[3] / MPU66050_CALIB_OFFSET_NB_MES;
    gyroYoffset = ag[4] / MPU66050_CALIB_OFFSET_NB_MES;
    gyroZoffset = ag[5] / MPU66050_CALIB_OFFSET_NB_MES;
}
void update(){
  // retrieve raw data
  fetchData();
  
  // estimate tilt angles: this is an approximation for small angles!
  float sgZ = accZ<0 ? -1 : 1; // allow one angle to go from -180 to +180 degrees
  angleAccX =   atan2(accY, sgZ*sqrt(accZ*accZ + accX*accX)) * RAD_2_DEG; // [-180,+180] deg
  angleAccY = - atan2(accX,     sqrt(accZ*accZ + accY*accY)) * RAD_2_DEG; // [- 90,+ 90] deg

  float dt = 10 * 1e-3;

  // Correctly wrap X and Y angles (special thanks to Edgar Bonet!)
  // https://github.com/gabriel-milan/TinyMPU6050/issues/6
  angleX = wrap(filterGyroCoef*(angleAccX + wrap(angleX +     gyroX*dt - angleAccX,180)) + (1.0-filterGyroCoef)*angleAccX,180);
  angleY = wrap(filterGyroCoef*(angleAccY + wrap(angleY + sgZ*gyroY*dt - angleAccY, 90)) + (1.0-filterGyroCoef)*angleAccY, 90);
  angleZ = wrap(gyroZ*dt+angleZ,180); // not wrapped

}


#endif
void Gyro_getAngles(float *angles)
{
	
#if  defined(MPU6050)
	angles[0]= angleX;
	angles[1]= angleY;
	angles[2]= angleZ;
#else
	angles[0] =  0;
#endif
}
void GYRO_init(void){
	
	
#if  defined(A3G)
	uint8_t buf[] = {A3G_CTRL_REG4 , 0x1 << 6};
	//max BW & data rate with enabling
	//I2C_myTransmit(I2C2,A3G_I2C_ADDRESS,buf,2);
	buf[0] = A3G_CTRL_REG1;
	buf[1] = 0x0F;
	I2C_myTransmit(I2C2,A3G_I2C_ADDRESS,buf,2);
	I2C_myRequest(I2C2,A3G_I2C_ADDRESS,A3G_CTRL_REG4,buf,1);
	buf[1]=10;
	GYRO_test();
#elif defined(IAM)
	//don't need i think
#elif defined(MPU6050) 
	uint8_t buf[] = {MPU6050_PWR_MGMT_1 , 0x01}; 
	I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
	buf[0] = MPU6050_SMPLRT_DIV;
	buf[1] = 0x00;
	I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
	buf[0] = MPU6050_CONFIG;
	buf[1] = 0x00;
	I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
	buf[0] = MPU6050_GYRO_CONFIG;
	buf[1] = 0x00;
	I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
	buf[0] = MPU6050_ACCEL_CONFIG;
	buf[1] = 0x00;
	I2C_myTransmit(I2C2,MPU6050_I2C_ADDRESS,buf,2);
	calcOffsets();
#else
	//nothing
	
#endif
	
}
void GYRO_Read(float *data){
  
#if  defined(A3G)
	uint8_t reader[6] = {0};
  I2C_myRequest(I2C2,A3G_I2C_ADDRESS,A3G_OUT_X_L|0x80,reader,6);
  data[0] = (float)((int16_t)((reader[1]<< 8) | reader[0])) * 0.00875f - test[0];
  data[1] = (float)((int16_t)((reader[3]<< 8) | reader[2])) * 0.00875f - test[1];
  data[2] = (float)((int16_t)((reader[5]<< 8) | reader[4])) * 0.00875f - test[2];
#elif defined(IAM)
  uint8_t reader[6] = {0};
  I2C_myRequest(I2C2,IAM_I2C_ADDRESS,IAM_XOUT_H,reader,6);
  data[0] = (float)((int16_t)((reader[0]<< 8) | reader[1])) / 131f ;
  data[1] = (float)((int16_t)((reader[2]<< 8) | reader[3])) * 131f;
  data[2] = (float)((int16_t)((reader[4]<< 8) | reader[5])) * 131f;
#elif defined(MPU6050)
  
  update();
  data[0] = gyroX;
  data[1] = gyroY;
  data[2] = gyroZ;
#else
  data[0] = 50.6 ;
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