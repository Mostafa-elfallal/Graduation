/**
  ******************************************************************************
  * @file    MRAM.c
  * @author  Mostafa ElFallal
  * @date    15-April-2022
  ******************************************************************************
*/
#include "MRAM.h"

//32 K byte
#ifndef  USE_MRAM
	uint8_t * MRAMARR;
#endif
void MRAM_init(void)
{
#ifdef USE_MRAM
  SPI_CS_HIGH(MRAM_CS_PORT,MRAM_CS_PIN);
#else
  MRAMARR = pvPortMalloc(32*1024*sizeof(uint8_t));
#endif
}
void MRAM_writeEnable(void)
{
#ifdef USE_MRAM
    /*!< Select the FLASH: Chip Select low */
  SPI_CS_LOW(MRAM_CS_PORT,MRAM_CS_PIN);

  /*!< Send "Write Enable" instruction */
  SPI_SendByte(SPI2,MRAM_WREN);

  /*!< Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(MRAM_CS_PORT,MRAM_CS_PIN);
#endif
}
void MRAM_readBuffer(uint16_t address,uint8_t *Buffer,uint16_t len)
{
#ifdef USE_MRAM
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
#else
  for(uint8_t i = 0;i<len;i++)
  {
	 Buffer[i]=MRAMARR[address+i]; 
  }
#endif 
}
void MRAM_writeBuffer(uint16_t address,uint8_t *Buffer,uint16_t len)
{
#ifdef USE_MRAM
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
#else
	for(uint8_t i = 0;i<len;i++)
	{
		MRAMARR[address+i] = Buffer[i]; 
	}
#endif
}