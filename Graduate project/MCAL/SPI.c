#include "SPI.h"

void SPI_Init(SPI_TypeDef* SPIx)
{
  SPIx->CR1 |= (uint16_t)((uint32_t)SPI_Direction_2Lines_FullDuplex | SPI_Mode_Master |
                  SPI_DataSize_8b | SPI_CPOL_Low |  
                  SPI_CPHA_1Edge | SPI_NSS_Soft |  
                SPI_BaudRatePrescaler_32 | SPI_FirstBit_MSB);
  SPIx->CR1 |= SPI_CR1_SPE; //enable
}

uint8_t SPI_ReceiveByte(SPI_TypeDef* SPIx,uint8_t Dummy)
{
  return (SPI_SendByte(SPIx,Dummy));
}

uint8_t SPI_SendByte(SPI_TypeDef* SPIx,uint8_t byte)
{
  /*!< Loop while DR register in not empty */
  while ( (SPIx->SR & SPI_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPIx->DR = byte;

  /*!< Wait to receive a byte */
  while ((SPIx->SR & SPI_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return SPIx->DR;
}