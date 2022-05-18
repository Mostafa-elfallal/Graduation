/**
  ******************************************************************************
  * @file    MRAM.h
  * @author  Mostafa ElFallal
  * @date    15-April-2022
  ******************************************************************************
*/
#ifndef __MRAM_H__
#define __MRAM_H__
#include "main.h"

#define     MRAM_DUMMY_BYTE     0xFF

#define     MRAM_CS_PORT        GPIOA
#define     MRAM_CS_PIN         GPIO_Pin_4
#define     MRAM_WP_PORT        GPIOG
#define     MRAM_WP_PIN         GPIO_Pin_11
#define     MRAM_HOLD_PORT      GPIOG
#define     MRAM_HOLD_PIN       GPIO_Pin_12

#define     MRAM_WREN           0x06    /*Write Enable          */
#define     MRAM_WRDI           0x04    /*Write Disable         */
#define     MRAM_RDSR           0x05    /*Read  Status  Register*/
#define     MRAM_WRSR           0x01    /*Write Status  Register*/
#define     MRAM_READ           0x03    /*Read  Data    Bytes   */
#define     MRAM_WRITE          0x02    /*Write Data    Bytes   */
#define     MRAM_SLEEP          0xB9    /*Enter Sleep   Mode    */
#define     MRAM_WAKE           0xAB    /*Exit  Sleep   Mode    */


void MRAM_init(void);
void MRAM_writeEnable(void);
void MRAM_readBuffer(uint16_t address,uint8_t *Buffer,uint16_t len);
void MRAM_writeBuffer(uint16_t address,uint8_t *Buffer,uint16_t len);

#endif