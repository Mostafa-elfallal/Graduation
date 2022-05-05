/**
  * @file    main.h
  * @author  Mostafa ElFallal
  * @date    04-November-2021
  * @brief   project header
  */
  
#ifndef __MAIN_H_
#define __MAIN_H_
//Device 
#include "stdint.h"
#include "stm32f4xx.h"
//MCAL
#include "RCC.h"
#include "GPIO.h"
#include "USART.h"
#include "I2C.h"
#include "ADC.h"
#include "TMR.h"
#include "SPI.h"
#include "FLASH.h"
//HAL
#define LIS2
//#define LIS3

//#define A3G
//#define IAM
#define MPU6050
#include "Gyroscope.h"
#include "magnetometer.h"
#include "Temp_STDS75.h"
#include "MRAM.h"
#include "FROM.h"
//Services
#include "SSP.h"
#include "SSP_funcs.h"
//FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/*
    **********************************************************************
    *   use #define LIS2 or LIS3 to include any of them as a magnetic sensor
    *   otherwise error will be raised
    *
    *
    **********************************************************************
*/

#define BAUDRATE                    9600
#define FESC                        0xdb
#define DEST                        0
#define SRC                         1
#define TYPE                        2
#define PING                        0
#define INIT                        1
#define ACK                         2
#define NACK                        3
#define GET                         4
#define PUT                         5
#define READ                        6
#define WRITE                       7
#define ID                          8
#define ADDRT                       54
#define DELRT                       55
#define GETRT                       56    
#define FEND                        0xC0
#define ADCS_ADDRESS                0x07
#define OBC_ADDRESS                 0x01
#define STDS75_ADDRESS              0x48    //0b1001000
#define GREENLED_PORT           GPIOA
#define GREENLED                GPIO_Pin_9

#define REDLED_PORT             GPIOD
#define REDLED                  GPIO_Pin_5

#define USER_GREENLED_PORT      GPIOD
#define USER_GREENLED           GPIO_Pin_12

#define USER_REDLED_PORT        GPIOD
#define USER_REDLED             GPIO_Pin_14

#define USER_ORANGELED_PORT     GPIOD
#define USER_ORANGELED          GPIO_Pin_13

#define USER_BLUELED_PORT       GPIOD
#define USER_BLUELED            GPIO_Pin_15




#endif
