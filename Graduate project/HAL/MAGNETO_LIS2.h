/**
  ******************************************************************************
  * @file    MAGNETO_LIS2.h
  * @author  Mostafa ElFallal
  * @date    20-March-2022
  ******************************************************************************
*/
#ifndef __LIS2_H_
#define __LIS2_H_

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define LIS2MDL_ADDRESS_MAG 0x1E   //!< Default address
#define LIS2MDL_CHIP_ID 0x40       //!< Chip ID from WHO_AM_I register
#define LIS2MDL_MAG_LSB 1.5 //!< Sensitivity
#define LIS2MDL_MILLIGAUSS_TO_MICROTESLA                                       \
  0.1 //!< Conversion rate of Milligauss to Microtesla
/*=========================================================================*/

/*!
 * @brief LIS2MDL I2C register address bits
 */
typedef enum {
  LIS2MDL_OFFSET_X_REG_L = 0x45,
  LIS2MDL_OFFSET_X_REG_H = 0x46,
  LIS2MDL_OFFSET_Y_REG_L = 0x47,
  LIS2MDL_OFFSET_Y_REG_H = 0x48,
  LIS2MDL_OFFSET_Z_REG_L = 0x49,
  LIS2MDL_OFFSET_Z_REG_H = 0x4A,
  LIS2MDL_WHO_AM_I = 0x4F,
  LIS2MDL_CFG_REG_A = 0x60,
  LIS2MDL_CFG_REG_B = 0x61,
  LIS2MDL_CFG_REG_C = 0x62,
  LIS2MDL_INT_CRTL_REG = 0x63,
  LIS2MDL_INT_SOURCE_REG = 0x64,
  LIS2MDL_INT_THS_L_REG = 0x65,
  LIS2MDL_STATUS_REG = 0x67,
  LIS2MDL_OUTX_L_REG = 0x68,
  LIS2MDL_OUTX_H_REG = 0x69,
  LIS2MDL_OUTY_L_REG = 0x6A,
  LIS2MDL_OUTY_H_REG = 0x6B,
  LIS2MDL_OUTZ_L_REG = 0x6C,
  LIS2MDL_OUTZ_H_REG = 0x6D,
} lis2mdl_register_t;
/*=========================================================================*/

/*!
 * @brief Magnetometer update rate settings
 */
typedef enum {
  LIS2MDL_RATE_10_HZ,  //!< 10 Hz
  LIS2MDL_RATE_20_HZ,  //!< 20 Hz
  LIS2MDL_RATE_50_HZ,  //!< 50 Hz
  LIS2MDL_RATE_100_HZ, //!< 100 Hz
} lis2mdl_rate_t;
/*=========================================================================*/

/**************************************************************************/
/*!
    @brief  a data thing
*/
/**************************************************************************/
typedef struct{
  int16_t x; ///< x-axis raw data
  int16_t y; ///< y-axis raw data
  int16_t z; ///< z-axis raw data
} MAGNETO_data_t;
/*=========================================================================*/

#endif