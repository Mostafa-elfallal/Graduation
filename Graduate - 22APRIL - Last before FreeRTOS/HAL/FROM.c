/**
  ******************************************************************************
  * @file    FROM.c
  * FLASH ROM
  * @author  Mostafa ElFallal
  * @date    19-April-2022
  ******************************************************************************
*/
#include "FROM.h"

void FROM_init(void)
{
  SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);
}
/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void FROM_WriteEnable(void)
{
  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(FROM_CS_PORT,FROM_CS_PIN);
  
  /*!< Send "Write Enable" instruction */
  SPI_SendByte(SPI2,FROM_WREN);
  
  /*!< Deselect the FLASH: Chip Select high */
   SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);
}
/**
  * @brief  Erases the specified FLASH sector.
  * @param  SectorAddr: address of the sector to erase.
  * @retval None
  */
void FROM_EraseSector(uint32_t SectorAddr)
{
  /*!< Send write enable instruction */
  FROM_WriteEnable();

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(FROM_CS_PORT,FROM_CS_PIN);
  /*!< Send Sector Erase instruction */
  SPI_SendByte(SPI2,FROM_SER);
  /*!< Send SectorAddr high nibble address byte */
  SPI_SendByte(SPI2,(SectorAddr & 0xFF0000) >> 16);
  /*!< Send SectorAddr medium nibble address byte */
  SPI_SendByte(SPI2,(SectorAddr & 0xFF00) >> 8);
  /*!< Send SectorAddr low nibble address byte */
  SPI_SendByte(SPI2,SectorAddr & 0xFF);
  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);

  /*!< Wait the end of Flash writing */
  FROM_WaitForWriteEnd();
}
/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
void FROM_WaitForWriteEnd(void)
{
  uint8_t flashstatus = 0;

  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(FROM_CS_PORT,FROM_CS_PIN);

  /*!< Send "Read Status Register" instruction */
  SPI_SendByte(SPI2,FROM_RDSR);

  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    flashstatus = SPI_ReceiveByte(SPI2,FROM_DUMMY_BYTE);

  }
  while ((flashstatus & FROM_WIP_FLAG) == FROM_WIP_FLAG); /* Write in progress */

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);
}
/**
  * @brief  Erases the entire FLASH.
  * @param  None
  * @retval None
  */
void sFLASH_EraseBulk(void)
{
  /*!< Send write enable instruction */
  FROM_WriteEnable();

  /*!< Bulk Erase */
  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(FROM_CS_PORT,FROM_CS_PIN);
  /*!< Send Bulk Erase instruction  */
  SPI_SendByte(SPI2,FROM_CER);
  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);

  /*!< Wait the end of Flash writing */
  FROM_WaitForWriteEnd();
}

/**
  * @brief  Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
  * @note   The number of byte can't exceed the FLASH page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH, must be equal
  *         or less than "sFLASH_PAGESIZE" value.
  * @retval None
  */
void FROM_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint8_t NumByteToWrite)
{
  /*!< Enable the write access to the FLASH */
  FROM_WriteEnable();

  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(FROM_CS_PORT,FROM_CS_PIN);
  /*!< Send "Write to Memory " instruction */
  SPI_SendByte(SPI2,FROM_PP);
  /*!< Send WriteAddr high nibble address byte to write to */
  SPI_SendByte(SPI2,(WriteAddr & 0xFF0000) >> 16);
  /*!< Send WriteAddr medium nibble address byte to write to */
  SPI_SendByte(SPI2,(WriteAddr & 0xFF00) >> 8);
  /*!< Send WriteAddr low nibble address byte to write to */
  SPI_SendByte(SPI2,WriteAddr & 0xFF);

  /*!< while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /*!< Send the current byte */
    SPI_SendByte(SPI2,*pBuffer);
    /*!< Point on the next byte to be written */
    pBuffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);

  /*!< Wait the end of Flash writing */
  FROM_WaitForWriteEnd();
}

/**
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(FROM_CS_PORT,FROM_CS_PIN);

  /*!< Send "Read from Memory " instruction */
  SPI_SendByte(SPI2,FROM_NORD);

  /*!< Send ReadAddr high nibble address byte to read from */
  SPI_SendByte(SPI2,(ReadAddr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte to read from */
  SPI_SendByte(SPI2,(ReadAddr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte to read from */
  SPI_SendByte(SPI2,ReadAddr & 0xFF);

  while (NumByteToRead--) /*!< while there is data to be read */
  {
    /*!< Read a byte from the FLASH */
    *pBuffer = SPI_SendByte(SPI2,FROM_DUMMY_BYTE);
    /*!< Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(FROM_CS_PORT,FROM_CS_PIN);
}
