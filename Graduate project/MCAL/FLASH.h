/**
  ******************************************************************************
  * @file    FLASH.h
  * @author  Mostafa ElFallal
  * @date    19-April-2022
  *****************************************************************************
*/
#ifndef __FLASH_H_
#define __FLASH_H_

#include "stm32f4xx.h"
#include "stdint.h"
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_RD,
  FLASH_ERROR_PGS,
  FLASH_ERROR_PGP,
  FLASH_ERROR_PGA,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_ERROR_OPERATION,
  FLASH_COMPLETE
}FLASH_Status;

#define FLASH_Latency_0                ((uint8_t)0x0000)  /*!< FLASH Zero Latency cycle      */
#define FLASH_Latency_1                ((uint8_t)0x0001)  /*!< FLASH One Latency cycle       */
#define FLASH_Latency_2                ((uint8_t)0x0002)  /*!< FLASH Two Latency cycles      */
#define FLASH_Latency_3                ((uint8_t)0x0003)  /*!< FLASH Three Latency cycles    */
#define FLASH_Latency_4                ((uint8_t)0x0004)  /*!< FLASH Four Latency cycles     */
#define FLASH_Latency_5                ((uint8_t)0x0005)  /*!< FLASH Five Latency cycles     */
#define FLASH_Latency_6                ((uint8_t)0x0006)  /*!< FLASH Six Latency cycles      */
#define FLASH_Latency_7                ((uint8_t)0x0007)  /*!< FLASH Seven Latency cycles    */
#define FLASH_Latency_8                ((uint8_t)0x0008)  /*!< FLASH Eight Latency cycles    */
#define FLASH_Latency_9                ((uint8_t)0x0009)  /*!< FLASH Nine Latency cycles     */
#define FLASH_Latency_10               ((uint8_t)0x000A)  /*!< FLASH Ten Latency cycles      */
#define FLASH_Latency_11               ((uint8_t)0x000B)  /*!< FLASH Eleven Latency cycles   */
#define FLASH_Latency_12               ((uint8_t)0x000C)  /*!< FLASH Twelve Latency cycles   */
#define FLASH_Latency_13               ((uint8_t)0x000D)  /*!< FLASH Thirteen Latency cycles */
#define FLASH_Latency_14               ((uint8_t)0x000E)  /*!< FLASH Fourteen Latency cycles */
#define FLASH_Latency_15               ((uint8_t)0x000F)  /*!< FLASH Fifteen Latency cycles  */

#define VoltageRange_1        ((uint8_t)0x00)  /*!< Device operating range: 1.8V to 2.1V */
#define VoltageRange_2        ((uint8_t)0x01)  /*!<Device operating range: 2.1V to 2.7V */
#define VoltageRange_3        ((uint8_t)0x02)  /*!<Device operating range: 2.7V to 3.6V */
#define VoltageRange_4        ((uint8_t)0x03)  /*!<Device operating range: 2.7V to 3.6V + External Vpp */

#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< Sector Number 0   */
#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< Sector Number 1   */
#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< Sector Number 2   */
#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< Sector Number 3   */
#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< Sector Number 4   */
#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< Sector Number 5   */
#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< Sector Number 6   */
#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< Sector Number 7   */
#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< Sector Number 8   */
#define FLASH_Sector_9     ((uint16_t)0x0048) /*!< Sector Number 9   */
#define FLASH_Sector_10    ((uint16_t)0x0050) /*!< Sector Number 10  */
#define FLASH_Sector_11    ((uint16_t)0x0058) /*!< Sector Number 11  */

#define OB_WRP_Sector_0       ((uint32_t)0x00000001) /*!< Write protection of Sector0     */
#define OB_WRP_Sector_1       ((uint32_t)0x00000002) /*!< Write protection of Sector1     */
#define OB_WRP_Sector_2       ((uint32_t)0x00000004) /*!< Write protection of Sector2     */
#define OB_WRP_Sector_3       ((uint32_t)0x00000008) /*!< Write protection of Sector3     */
#define OB_WRP_Sector_4       ((uint32_t)0x00000010) /*!< Write protection of Sector4     */
#define OB_WRP_Sector_5       ((uint32_t)0x00000020) /*!< Write protection of Sector5     */
#define OB_WRP_Sector_6       ((uint32_t)0x00000040) /*!< Write protection of Sector6     */
#define OB_WRP_Sector_7       ((uint32_t)0x00000080) /*!< Write protection of Sector7     */
#define OB_WRP_Sector_8       ((uint32_t)0x00000100) /*!< Write protection of Sector8     */
#define OB_WRP_Sector_9       ((uint32_t)0x00000200) /*!< Write protection of Sector9     */
#define OB_WRP_Sector_10      ((uint32_t)0x00000400) /*!< Write protection of Sector10    */
#define OB_WRP_Sector_11      ((uint32_t)0x00000800) /*!< Write protection of Sector11    */

#define OB_PcROP_Disable   ((uint8_t)0x00) /*!< Disabled PcROP, nWPRi bits used for Write Protection on sector i */
#define OB_PcROP_Enable    ((uint8_t)0x80) /*!< Enable PcROP, nWPRi bits used for PCRoP Protection on sector i   */

#define OB_PCROP_Sector_0        ((uint32_t)0x00000001) /*!< PC Read/Write protection of Sector0      */
#define OB_PCROP_Sector_1        ((uint32_t)0x00000002) /*!< PC Read/Write protection of Sector1      */
#define OB_PCROP_Sector_2        ((uint32_t)0x00000004) /*!< PC Read/Write protection of Sector2      */
#define OB_PCROP_Sector_3        ((uint32_t)0x00000008) /*!< PC Read/Write protection of Sector3      */
#define OB_PCROP_Sector_4        ((uint32_t)0x00000010) /*!< PC Read/Write protection of Sector4      */
#define OB_PCROP_Sector_5        ((uint32_t)0x00000020) /*!< PC Read/Write protection of Sector5      */
#define OB_PCROP_Sector_6        ((uint32_t)0x00000040) /*!< PC Read/Write protection of Sector6      */
#define OB_PCROP_Sector_7        ((uint32_t)0x00000080) /*!< PC Read/Write protection of Sector7      */
#define OB_PCROP_Sector_8        ((uint32_t)0x00000100) /*!< PC Read/Write protection of Sector8      */
#define OB_PCROP_Sector_9        ((uint32_t)0x00000200) /*!< PC Read/Write protection of Sector9      */
#define OB_PCROP_Sector_10       ((uint32_t)0x00000400) /*!< PC Read/Write protection of Sector10     */
#define OB_PCROP_Sector_11       ((uint32_t)0x00000800) /*!< PC Read/Write protection of Sector11     */

#define OB_RDP_Level_0   ((uint8_t)0xAA)
#define OB_RDP_Level_1   ((uint8_t)0x55)

#define OB_IWDG_SW                     ((uint8_t)0x20)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */

#define OB_STOP_NoRST                  ((uint8_t)0x40) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */

#define OB_STDBY_NoRST                 ((uint8_t)0x80) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */

#define OB_BOR_LEVEL3          ((uint8_t)0x00)  /*!< Supply voltage ranges from 2.70 to 3.60 V */
#define OB_BOR_LEVEL2          ((uint8_t)0x04)  /*!< Supply voltage ranges from 2.40 to 2.70 V */
#define OB_BOR_LEVEL1          ((uint8_t)0x08)  /*!< Supply voltage ranges from 2.10 to 2.40 V */
#define OB_BOR_OFF             ((uint8_t)0x0C)  /*!< Supply voltage ranges from 1.62 to 2.10 V */

#define OB_Dual_BootEnabled   ((uint8_t)0x10) /*!< Dual Bank Boot Enable                             */
#define OB_Dual_BootDisabled  ((uint8_t)0x00) /*!< Dual Bank Boot Disable, always boot on User Flash */

#define FLASH_IT_EOP                   ((uint32_t)0x01000000)  /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_ERR                   ((uint32_t)0x02000000)  /*!< Error Interrupt source */

#define FLASH_FLAG_EOP                 ((uint32_t)0x00000001)  /*!< FLASH End of Operation flag               */
#define FLASH_FLAG_OPERR               ((uint32_t)0x00000002)  /*!< FLASH operation Error flag                */
#define FLASH_FLAG_WRPERR              ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag          */
#define FLASH_FLAG_PGAERR              ((uint32_t)0x00000020)  /*!< FLASH Programming Alignment error flag    */
#define FLASH_FLAG_PGPERR              ((uint32_t)0x00000040)  /*!< FLASH Programming Parallelism error flag  */
#define FLASH_FLAG_PGSERR              ((uint32_t)0x00000080)  /*!< FLASH Programming Sequence error flag     */
#define FLASH_FLAG_RDERR               ((uint32_t)0x00000100)  /*!< Read Protection error flag (PCROP)        */
#define FLASH_FLAG_BSY                 ((uint32_t)0x00010000)  /*!< FLASH Busy flag                           */ 

#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD           ((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)0x00000300)
#define CR_PSIZE_MASK              ((uint32_t)0xFFFFFCFF)

#define RDP_KEY                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)
#define FLASH_OPT_KEY1           ((uint32_t)0x08192A3B)
#define FLASH_OPT_KEY2           ((uint32_t)0x4C5D6E7F)


/** 
  * @brief   ACR register byte 0 (Bits[7:0]) base address  
  */ 
#define ACR_BYTE0_ADDRESS           ((uint32_t)0x40023C00) 
/** 
  * @brief   OPTCR register byte 0 (Bits[7:0]) base address  
  */ 
#define OPTCR_BYTE0_ADDRESS         ((uint32_t)0x40023C14)
/** 
  * @brief   OPTCR register byte 1 (Bits[15:8]) base address  
  */ 
#define OPTCR_BYTE1_ADDRESS         ((uint32_t)0x40023C15)
/** 
  * @brief   OPTCR register byte 2 (Bits[23:16]) base address  
  */ 
#define OPTCR_BYTE2_ADDRESS         ((uint32_t)0x40023C16)
/** 
  * @brief   OPTCR register byte 3 (Bits[31:24]) base address  
  */ 
#define OPTCR_BYTE3_ADDRESS         ((uint32_t)0x40023C17)

/** 
  * @brief   OPTCR1 register byte 0 (Bits[7:0]) base address  
  */ 
#define OPTCR1_BYTE2_ADDRESS         ((uint32_t)0x40023C1A)

void FLASH_init(void);
void FLASH_writeWord(uint32_t Address,uint32_t Word);
uint32_t FLASH_readWord(uint32_t Address);
void FLASH_lock(void);
void FLASH_unlock(void);
void FLASH_sectorErase(uint8_t sectorNumber);
#endif 