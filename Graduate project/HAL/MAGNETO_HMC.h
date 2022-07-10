/**
  ******************************************************************************
  * @file    MAGNETO_HMC.h
  * @author  Mostafa ElFallal
  * @date    25-June-2022
  ******************************************************************************
*/
#ifndef __HMC5883_H__
#define __HMC5883_H__

#define HMC5883_ADDRESS 		0x1E

#define HMC5883_CRA_REG_M 		0x00
#define HMC5883_CRB_REG_M		0x01
#define HMC5883_MR_REG_M  		0x02
#define HMC5883_OUT_X_H_M 		0x03
#define HMC5883_OUT_X_L_M 		0x04
#define HMC5883_OUT_Z_H_M 		0x05
#define HMC5883_OUT_Z_L_M 		0x06
#define HMC5883_OUT_Y_H_M 		0x07
#define HMC5883_OUT_Y_L_M 		0x08
#define HMC5883_SR_REG_Mg  	0x09
#define HMC5883_IRA_REG_M 		0x0A
#define HMC5883_IRB_REG_M  	0x0B
#define HMC5883_IRC_REG_M  	0x0C
#define HMC5883_TEMP_OUT_H_M 	0x31
#define HMC5883_TEMP_OUT_L_M  	0x32

#endif