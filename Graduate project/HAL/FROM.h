/**
  ******************************************************************************
  * @file    FROM.h
  * FLASH ROM
  * @author  Mostafa ElFallal
  * @date    19-April-2022
  ******************************************************************************
*/
#ifndef __FROM_H__
#define __FROM_H__
#include "main.h"

#define     FROM_DUMMY_BYTE     0xA5
//FLASH 
// CE SPI2_MISO WP1 HOLD1 SPI2_SCK SPI2_MOSI
// WP1 = PG9 HOLD1 = PG10 CE = PB12
#define     FROM_CS_PORT         GPIOB
#define     FROM_CS_PIN          GPIO_Pin_12
#define     FROM_WP_PORT         GPIOG
#define     FROM_WP_PIN          GPIO_Pin_9
#define     FROM_HOLD_PORT       GPIOG
#define     FROM_HOLD_PIN        GPIO_Pin_10

#define     FROM_NORD           0x03    /*  Normal Read Mode                */
#define     FROM_FRD            0x0B    /*  Fast Read Mode                  */
#define     FROM_FRDIO          0xBB    /*  Fast Read Dual I/O              */
#define     FROM_FRDO           0x3B    /*  Fast Read Dual Output           */
#define     FROM_FRQIO          0xEB    /*  Fast Read Quad I/O              */
#define     FROM_FRQO           0x6B    /*  Fast Read Quad Output           */
#define     FROM_FRDDTR         0xBD    /*  Fast Read Dual I/O DTR          */
#define     FROM_FRQDTR         0xED    /*  Fast Read Quad I/O DTR          */
#define     FROM_PP             0x02    /*  Input Page Program              */
#define     FROM_PPQ            0x32    /*  Quad Input Page Program         */
#define     FROM_SER            0xD7    /*  Sector Erase                    */
#define     FROM_BER32          0x52    /*  Block Erase 32KB                */
#define     FROM_BER64          0xD8    /*  Block Erase 64KB                */
#define     FROM_CER            0xC7    /*  Chip Erase                      */
#define     FROM_WREN           0x06    /*  Write Enable                    */
#define     FROM_WRDI           0x04    /*  Write Disable                   */
#define     FROM_RDSR           0x05    /*  Read Status Register            */
#define     FROM_WRSR           0x01    /*  Write Status Register           */
#define     FROM_RDFR           0x48    /*  Read Function Register          */
#define     FROM_WRFR           0x42    /*  Write Function Register         */
#define     FROM_QPIEN          0x35    /*  Enter QPI Mode                  */
#define     FROM_QPIDI          0xF5    /*  Exit QPI Mode                   */
#define     FROM_PERSUS         0x75    /*  Suspend during program/erase    */
#define     FROM_PERRSM         0x7A    /*  Resume program/erase            */
#define     FROM_DP             0xB9    /*  Deep Power Down                 */
#define     FROM_RDID           0xAB    /*  Release ID/Release Power Down   */
#define     FROM_SRP            0xC0    /*  Set Read Parameters             */
#define     FROM_RDJDID         0x9F    /*  Read JEDEC ID Command           */
#define     FROM_RDMDID         0x90    /*  Read Manufacturer & Device ID   */
#define     FROM_RDJDIDQ        0xAF    /*  Read JEDEC ID QPI mode          */
#define     FROM_RDUID          0x4B    /*  Read Unique ID                  */
#define     FROM_RDSFDP         0x5A    /*  SFDP Read                       */
#define     FROM_RSTEN          0x66    /*  Software Reset Enable           */
#define     FROM_RST            0x99    /*  Software Reset Erase            */
#define     FROM_IRER           0x64    /*  Erase Information Row           */
#define     FROM_IRP            0x62    /*  Program Information Row         */
#define     FROM_IRRD           0x68    /*  Read Information Row            */
#define     FROM_SECUNLOCK      0x26    /*  Sector Unlock                   */
#define     FROM_SECLOCK        0x24    /*  Sector Lock                     */

#define     FROM_WIP_FLAG       0x01    /*  Write In Progress (WIP) flag     */

void FROM_init(void);
void FROM_WriteEnable(void);
void FROM_EraseSector(uint32_t SectorAddr);
void FROM_WaitForWriteEnd(void);
void sFLASH_EraseBulk(void);
void FROM_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint8_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

#endif