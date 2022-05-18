/**
  ******************************************************************************
  * @file    SPI.h
  * @author  Mostafa ElFallal
  * @date    17-April-2022
  ******************************************************************************
*/
#ifndef _SPI_H__
#define _SPI_H__

#include "GPIO.h" //for SS bits
#include "stdint.h"
#include "RCC.h"
#include "stm32f4xx.h"
/* Exported macro ------------------------------------------------------------*/
/* Select sFLASH: Chip Select pin low */
#define SPI_CS_LOW(PORT,PIN)       GPIO_ResetBits(PORT, PIN)
/* Deselect sFLASH: Chip Select pin high */
#define SPI_CS_HIGH(PORT,PIN)      GPIO_SetBits(PORT, PIN)  
/* Defines         -----------------------------------------------------------*/
#define SPI_Direction_2Lines_FullDuplex ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx          ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx          ((uint16_t)0xC000)


#define SPI_Mode_Master                 ((uint16_t)0x0104)
#define SPI_Mode_Slave                  ((uint16_t)0x0000)

#define SPI_DataSize_16b                ((uint16_t)0x0800)
#define SPI_DataSize_8b                 ((uint16_t)0x0000)

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0002)


#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0001)



#define SPI_NSS_Soft                    ((uint16_t)0x0200)
#define SPI_NSS_Hard                    ((uint16_t)0x0000)


#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038)

#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                ((uint16_t)0x0080)

#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)


#define SPI_Direction_Rx                ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                ((uint16_t)0x4000)


#define SPI_IT_TXE                      ((uint8_t)0x71)
#define SPI_IT_RXNE                     ((uint8_t)0x60)
#define SPI_IT_ERR                      ((uint8_t)0x50)
#define SPI_IT_TIFRFE                   ((uint8_t)0x58)


#define SPI_IT_OVR                      ((uint8_t)0x56)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_IT_CRCERR                   ((uint8_t)0x54)

#define SPI_FLAG_RXNE                   ((uint16_t)0x0001)
#define SPI_FLAG_TXE                    ((uint16_t)0x0002)
#define SPI_FLAG_CRCERR                 ((uint16_t)0x0010)
#define SPI_FLAG_MODF                   ((uint16_t)0x0020)
#define SPI_FLAG_OVR                    ((uint16_t)0x0040)
#define SPI_FLAG_BSY                    ((uint16_t)0x0080)
#define SPI_FLAG_TIFRFE                 ((uint16_t)0x0100)

/* Functions -----------------------------------------------------------*/

void SPI_Init(SPI_TypeDef* SPIx);
uint8_t SPI_ReceiveByte(SPI_TypeDef* SPIx,uint8_t Dummy);
uint8_t SPI_SendByte(SPI_TypeDef* SPIx,uint8_t byte);
#endif