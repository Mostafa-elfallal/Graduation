/**
  ******************************************************************************
  * @file    GYRO_A3G.h
  * @author  Mostafa ElFallal
  * @date    05-March-2022
  ******************************************************************************
*/
#ifndef __MPU__H_
#define __MPU__H_

#define A3G_CTRL_REG1               0x20
#define A3G_CTRL_REG2               0x21
#define A3G_CTRL_REG3               0x22
#define A3G_CTRL_REG4               0x23
#define A3G_CTRL_REG5               0x24
#define A3G_REF                     0x25
#define A3G_OUT_TEMP                0x26
#define A3G_STATUS_REG              0x27
#define A3G_OUT_X_L                 0x28
#define A3G_OUT_X_H                 0x29
#define A3G_OUT_Y_L                 0x2A
#define A3G_OUT_Y_H                 0x2B
#define A3G_OUT_Z_L                 0x2C
#define A3G_OUT_Z_H                 0x2D
#define A3G_FIFO_CTRL_REG           0x2E
#define A3G_FIFO_SRC_REG            0x2F
#define A3G_INT1_CFG                0x30
#define A3G_INT1_SRC                0x31
#define A3G_INT1_THS_XH             0x32
#define A3G_INT1_THS_XL             0x33
#define A3G_INT1_THS_YH             0x34
#define A3G_INT1_THS_YL             0x35
#define A3G_INT1_THS_ZH             0x36
#define A3G_INT1_THS_ZL             0x37
#define A3G_INT1_DURATION           0x38
#define A3G_WHO_AM_I                0x0F   // R
// Default I2C address for the MPU-6050 is 0x68.
// But only if the AD0 pin is low.
// Some sensor boards have AD0 high, and the
// I2C address thus becomes 0xD1.
#define A3G_I2C_ADDRESS 0b1101000