/**
  ******************************************************************************
  * @file    gpio.h
  * @author  Mostafa ElFallal
  * @date    04-November-2021
  * @brief   This file contains all the functions prototypes for the GPIO firmware
  *          library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

 
typedef enum
{ 
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;

typedef enum
{ 
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;

 
typedef enum
{ 
  GPIO_Low_Speed     = 0x00, /*!< Low speed    */
  GPIO_Medium_Speed  = 0x01, /*!< Medium speed */
  GPIO_Fast_Speed    = 0x02, /*!< Fast speed   */
  GPIO_High_Speed    = 0x03  /*!< High speed   */
}GPIOSpeed_TypeDef;

/* Add legacy definition */
#define  GPIO_Speed_2MHz    GPIO_Low_Speed    
#define  GPIO_Speed_25MHz   GPIO_Medium_Speed 
#define  GPIO_Speed_50MHz   GPIO_Fast_Speed 
#define  GPIO_Speed_100MHz  GPIO_High_Speed  
  

typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
}GPIOPuPd_TypeDef;

 
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;

typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef */

  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef */

  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef */
}GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/


#define GPIO_Pin_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              ((uint32_t)0x0000FFFF) /* PIN mask for assert test */

#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)


#define GPIO_AF_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping */
#define GPIO_AF_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping */
#define GPIO_AF_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping */

 
#define GPIO_AF_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */

#define GPIO_AF_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */


#define GPIO_AF_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping */
#define GPIO_AF_TIM9          ((uint8_t)0x03)  /* TIM9 Alternate Function mapping */
#define GPIO_AF_TIM10         ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define GPIO_AF_TIM11         ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */

#define GPIO_AF_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */

#define GPIO_AF_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3         ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping (Only for STM32F411xE and STM32F413_423xx Devices) */
#define GPIO_AF_SPI4          ((uint8_t)0x05)  /* SPI4/I2S4 Alternate Function mapping */
#define GPIO_AF_SPI5          ((uint8_t)0x05)  /* SPI5 Alternate Function mapping      */
#define GPIO_AF_SPI6          ((uint8_t)0x05)  /* SPI6 Alternate Function mapping      */


#define GPIO_AF_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_SPI1         ((uint8_t)0x06)  /* SPI1 Alternate Function mapping (Only for STM32F410xx Devices) */
#define GPIO_AF6_SPI2         ((uint8_t)0x06)  /* SPI2 Alternate Function mapping (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF6_SPI4         ((uint8_t)0x06)  /* SPI4 Alternate Function mapping (Only for STM32F411xE Devices) */
#define GPIO_AF6_SPI5         ((uint8_t)0x06)  /* SPI5 Alternate Function mapping (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF_SAI1          ((uint8_t)0x06)  /* SAI1 Alternate Function mapping      */
#define GPIO_AF_I2S2ext       ((uint8_t)0x06)  /* I2S2ext_SD Alternate Function mapping (only for STM32F412xG and STM32F413_423xx Devices) */


#define GPIO_AF_USART1         ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF_USART2         ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF_USART3         ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_SPI3          ((uint8_t)0x07)  /* SPI3/I2S3ext Alternate Function mapping */


#define GPIO_AF_I2S3ext   GPIO_AF7_SPI3

 
#define GPIO_AF_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping  */
#define GPIO_AF_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping  */
#define GPIO_AF_USART6        ((uint8_t)0x08)  /* USART6 Alternate Function mapping */
#define GPIO_AF_UART7         ((uint8_t)0x08)  /* UART7 Alternate Function mapping  */
#define GPIO_AF_UART8         ((uint8_t)0x08)  /* UART8 Alternate Function mapping  */


#define GPIO_AF_CAN1          ((uint8_t)0x09)  /* CAN1 Alternate Function mapping  */
#define GPIO_AF_CAN2          ((uint8_t)0x09)  /* CAN2 Alternate Function mapping  */
#define GPIO_AF_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define GPIO_AF_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define GPIO_AF_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */
#define GPIO_AF9_I2C2         ((uint8_t)0x09)  /* I2C2 Alternate Function mapping (Only for STM32F401xx/STM32F410xx/STM32F411xE/STM32F412xG/STM32F413_423xx Devices) */
#define GPIO_AF9_I2C3         ((uint8_t)0x09)  /* I2C3 Alternate Function mapping (Only for STM32F401xx/STM32F411xE/STM32F412xG and STM32F413_423xx Devices) */
#define GPIO_AF9_LTDC         ((uint8_t)0x09)  /* LTDC Alternate Function mapping */


#define GPIO_AF_OTG_FS         ((uint8_t)0xA)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF_OTG_HS         ((uint8_t)0xA)  /* OTG_HS Alternate Function mapping */

#define GPIO_AF_ETH             ((uint8_t)0x0B)  /* ETHERNET Alternate Function mapping */


#define GPIO_AF_FSMC             ((uint8_t)0xC)  /* FSMC Alternate Function mapping                     */

#define GPIO_AF_OTG_HS_FS        ((uint8_t)0xC)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF_SDIO             ((uint8_t)0xC)  /* SDIO Alternate Function mapping                     */


#define GPIO_AF_DCMI          ((uint8_t)0x0D)  /* DCMI Alternate Function mapping */

#define GPIO_AF_LTDC          ((uint8_t)0x0E)  /* LCD-TFT Alternate Function mapping */


#define GPIO_AF_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */


#define GPIO_Mode_AIN           GPIO_Mode_AN

#define GPIO_AF_OTG1_FS         GPIO_AF_OTG_FS
#define GPIO_AF_OTG2_HS         GPIO_AF_OTG_HS
#define GPIO_AF_OTG2_FS         GPIO_AF_OTG_HS_FS



/*  Function used to set the GPIO configuration to the default reset state ****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);

/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Read and Write functions **********************************************/
uint8_t GPIO_ReadInputBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputPort(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputPort(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* GPIO Alternate functions configuration function ****************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#endif 
