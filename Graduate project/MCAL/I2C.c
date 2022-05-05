/**
  ******************************************************************************
  * @file    I2C.h
  * @author  Mostafa ElFallal
  * @date    15-November-2021
  * @brief   This file contains all the functions prototypes for the I2C 
  ****************************************************************************** 
  */ 

/* Includes ------------------------------------------------------------------*/
#include "I2C.h"
#include "RCC.h"
#include "stdint.h"

#define CR1_CLEAR_MASK    ((uint16_t)0xFBF5)      /*<! I2C registers Masks */
#define FLAG_MASK         ((uint32_t)0x00FFFFFF)  /*<! I2C FLAG mask */
#define ITEN_MASK         ((uint32_t)0x07000000)  /*<! I2C Interrupt Enable mask */

#define TIMEOUT           ((uint32_t)0x07000000)  
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  if (I2Cx == I2C1)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);    
  }
  else if (I2Cx == I2C2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);      
  }
  else 
  {
    if (I2Cx == I2C3)
    {
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, DISABLE);     
    }
  }
}

void I2C_myInit(I2C_TypeDef* I2Cx){
    I2Cx->CR2 = 42;     // no interrupt and APB1 freq is 42 M
    I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_PE);    // disable I2C
    I2Cx->TRISE = (uint16_t)(((42 * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
    I2Cx->CCR =(uint16_t)(35 | I2C_CCR_FS);         // fast mode & 2:1 LOW , HIGh , 400K
    I2Cx->CR1 |= I2C_CR1_PE;                         // enable I2C
    I2Cx->CR1 |= I2C_Ack_Enable;
    I2Cx->OAR1 = 0x17 << 1;         // my I2C address
}
void I2C_myTransmit(I2C_TypeDef* I2Cx, uint8_t SAddr ,uint8_t * TxBuff , uint8_t size ){
  // in my case, iam the only master on the bus.
  // sequence : Start , address , data , stop 
  I2Cx->CR1 |= I2C_CR1_START;
  // wait for EV5 
  /* Wait SB flag is set */
  while(I2C_SR1_SB != (I2C_SR1_SB & I2Cx->SR1))
  {
    /* Do nothing */
  }
  (void)I2Cx->SR1;
  //cleared by reading SR1 then writing to DR
  //writing address with 0 in LSB to write

  //EV6  
  I2Cx->DR = (uint16_t)(SAddr<<1);
  /* Wait ADDR flag is set */
  while(I2C_SR1_ADDR != (I2C_SR1_ADDR & I2Cx->SR1))
  {
    /* Do nothing */
  }
  //cleared by reading SR1 then reading to SR2
  (void)I2Cx->SR1;
  (void)I2Cx->SR2;
  //EV8_1
  for (uint8_t i=0;i<size;i++)
  {
    while(I2C_SR1_TXE != (I2C_SR1_TXE & I2Cx->SR1))     // go out when Data is ACKed
    {
        /* Do nothing */
    }
    //cleared by writing data to DR
    I2Cx->DR = (uint16_t)TxBuff[i];
  }
  while(I2C_SR1_TXE != (I2C_SR1_TXE & I2Cx->SR1))     // go out when Data is ACKed
    {
        /* Do nothing */
    }
  //stop 
  I2Cx->CR1 |= I2C_CR1_STOP;
}
void I2C_myRequest(I2C_TypeDef* I2Cx, uint8_t SAddr , uint8_t RAddr ,uint8_t * RxBuff , uint8_t size ){
  // in my case, iam the only master on the bus.
  // sequence : Start , address , data , stop 
  /* Generate START */
  I2Cx->CR1 |= I2C_CR1_START;
  // wait for EV5 
  /* Wait SB flag is set */
  while(I2C_SR1_SB != (I2C_SR1_SB & I2Cx->SR1))
  {
    /* Do nothing */
  }
  (void)I2Cx->SR1;
  //cleared by reading SR1 then writing to DR
  //writing address with 0 in LSB to write
  I2Cx->DR = (SAddr<<1);
  //EV6
  /* Wait ADDR flag is set */
  while(I2C_SR1_ADDR != (I2C_SR1_ADDR & I2Cx->SR1))
  {
    /* Do nothing */
  }
  //cleared by reading SR1 then reading to SR2
  (void)I2Cx->SR1;
  (void)I2Cx->SR2;
  //EV8_1
  /* Wait TXE flag is set */
  while(I2C_SR1_TXE != (I2C_SR1_TXE & I2Cx->SR1))
  {
    /* Do nothing */
  }

  //cleared by writing data to DR 
if(2 <= size)
  {
    /* Acknowledge enable */
    I2Cx->CR1 |= I2C_CR1_ACK;

    /* Send register address to read with increment */
    I2Cx->DR = (uint16_t)RAddr; // is there a increment condition ?
  }
  else
  {
    /* Acknowledge disable */
    I2Cx->CR1 &= ~I2C_CR1_ACK;

    /* Send register address to read (single) */
    I2Cx->DR = (uint16_t)RAddr;
  }
  
  /* Wait BTF flag is set */
  while(I2C_SR1_BTF != (I2C_SR1_BTF & I2Cx->SR1))
  {
    /* Do nothing */
  }

  /* Generate ReSTART */
  I2Cx->CR1 |= I2C_CR1_START;

  /* Wait SB flag is set */
  while(I2C_SR1_SB != (I2C_SR1_SB & I2Cx->SR1))
  {
    /* Do nothing */
  }

  /* Read SR1 */
  (void)I2Cx->SR1;

  //cleared by reading SR1 then writing to DR
  //writing address with 1 in LSB to read
  I2Cx->DR = (uint16_t)((SAddr<<1) | 0x1);
  /* Wait ADDR flag is set */
  while(I2C_SR1_ADDR != (I2C_SR1_ADDR & I2Cx->SR1))
  {
    /* Do nothing */
  }
  (void)I2Cx->SR1;

  /* Read SR2 */
  (void)I2Cx->SR2;
  //EV7
  for(uint8_t i = 0;i<size ; i++)
  {
  while(I2C_SR1_RXNE != (I2C_SR1_RXNE & I2Cx->SR1))
  {
    /* Do nothing */
  }
    //cleared by reading data from DR
    RxBuff[i] = I2Cx->DR;
    if(i == size-2)
        I2Cx->CR1 &= ~I2C_CR1_ACK;
  }
  //stop 
  I2Cx->CR1 |= I2C_CR1_STOP;
}
void I2C_En(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CR1 |= I2C_CR1_PE;
  }
  else
  {
    I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_PE);
  }
}