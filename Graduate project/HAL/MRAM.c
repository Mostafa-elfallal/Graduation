/**
  ******************************************************************************
  * @file    MRAM.c
  * @author  Mostafa ElFallal
  * @date    15-April-2022
  ******************************************************************************
*/
#include "MRAM.h"

//32 K byte
void MRAM_init(void)
{
  SPI_CS_HIGH(MRAM_CS_PORT,MRAM_CS_PIN);
}
void MRAM_writeEnable(void)
{
    /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(MRAM_CS_PORT,MRAM_CS_PIN);

  /*!< Send "Write Enable" instruction */
  SPI_SendByte(SPI2,MRAM_WREN);

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(MRAM_CS_PORT,MRAM_CS_PIN);
}
void MRAM_readBuffer(uint16_t address,uint8_t *Buffer,uint16_t len)
{
   /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(MRAM_CS_PORT,MRAM_CS_PIN);

  /*!< Send "Read from Memory " instruction */
  SPI_SendByte(SPI2,MRAM_READ);

  /*!< Send ReadAddr high address byte to read from */
  SPI_SendByte(SPI2,(address& 0xFF00) >> 8);
  /*!< Send ReadAddr low address byte to read from */
  SPI_SendByte(SPI2,address & 0xFF);

  while (len--) /*!< while there is data to be read */
  {
    /*!< Read a byte from the FLASH */
    *Buffer = SPI_SendByte(SPI2,MRAM_DUMMY_BYTE);
    /*!< Point to the next location where the byte read will be saved */
    Buffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(MRAM_CS_PORT,MRAM_CS_PIN);
}
void MRAM_writeBuffer(uint16_t address,uint8_t *Buffer,uint16_t len)
{
  /*!< Enable the write access to the FLASH */
  MRAM_writeEnable();
  /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(MRAM_CS_PORT,MRAM_CS_PIN);
  /*!< Send "Write to Memory " instruction */
  SPI_SendByte(SPI2,MRAM_WRITE);
  /*!< Send ReadAddr high address byte to read from */
  SPI_SendByte(SPI2,(address& 0xFF00) >> 8);
  /*!< Send ReadAddr low address byte to read from */
  SPI_SendByte(SPI2,address & 0xFF);
   /*!< while there is data to be written on the FLASH */
  while (len--)
  {
    /*!< Send the current byte */
    SPI_SendByte(SPI2,*Buffer);
    /*!< Point on the next byte to be written */
    Buffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(MRAM_CS_PORT,MRAM_CS_PIN);
}