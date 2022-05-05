/**
******************************************************************************
* @file    FLASH.c
* @author  Mostafa ElFallal
* @date    19-April-2022
*****************************************************************************
*/

#include "FLASH.h"

void FLASH_init(void)
{
  FLASH->KEYR  =  FLASH_KEY1;
  FLASH->KEYR  =  FLASH_KEY2;
  FLASH->CR   &= ~FLASH_CR_PSIZE;
  FLASH->CR   |=  FLASH_CR_PSIZE_1;
  FLASH->CR   |=  FLASH_CR_LOCK;
}
void FLASH_unlock(void)
{
  FLASH->KEYR  =  FLASH_KEY1;
  FLASH->KEYR  =  FLASH_KEY2;
}
void FLASH_lock(void)
{
  FLASH->CR   |=  FLASH_CR_LOCK;
}
void FLASH_writeWord(uint32_t Address,uint32_t Word)
{
  
  while(0 != (FLASH->SR & FLASH_SR_BSY));
  FLASH->CR |= FLASH_CR_PG;
  *(volatile uint32_t*)(Address) = Word;
  while(0 != (FLASH->SR & FLASH_SR_BSY));
  FLASH->CR &= ~FLASH_CR_PG;
}
uint32_t FLASH_readWord(uint32_t Address)
{
  return (*(uint32_t *)Address);
}
void FLASH_sectorErase(uint8_t sectorNumber)
{
  while(0 != (FLASH->SR & FLASH_SR_BSY));
  FLASH->CR |= FLASH_CR_SER;
  FLASH->CR |= (sectorNumber<<3);
  FLASH->CR |= FLASH_CR_STRT;
  while(0 != (FLASH->SR & FLASH_SR_BSY));
    FLASH->CR &= ~FLASH_CR_SER;
}