/**
  ******************************************************************************
  * @file    USART.c
  * @author  Mostafa ElFAllal
  * @date    04-November-2021
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "USART.h"
#include "RCC.h"



#define IT_MASK                   ((uint16_t)0x001F)

void USART_myInit(USART_TypeDef* USARTx)
{
    uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  USARTx->CR2 = (uint16_t)0; // 1 stop bit
  USARTx->CR1 = (uint16_t)USART_Mode_Rx|USART_Mode_Tx; // enable TX and RX
  USARTx->CR3 = (uint16_t)0; // no flow control
  apbclock = 84000000;  // max clock in pclk2
  integerdivider = ((25 * apbclock) / (4 * (BAUDRATE)));    
  tmpreg = (integerdivider / 100) << 4;
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
  tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  USARTx->BRR = (uint16_t)tmpreg;
  NVIC_EnableIRQ(USART1_IRQn); // NVIC enable
    // interrupt types : RXNEIE
  USARTx->CR1 |= USART_CR1_RXNEIE;
  USARTx->CR1 |= USART_CR1_UE; // start uart
}

void USART_En(USART_TypeDef* USARTx, FunctionalState NewState)
{


  if (NewState != DISABLE)
  {
    USARTx->CR1 |= USART_CR1_UE;
  }
  else
  {
    USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_UE);
  }
}



void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{   
  while(USART_GetFlagStatus(USARTx , USART_FLAG_TXE) != SET);
  USARTx->DR = (Data & (uint16_t)0x01FF);
}

void USART_SendStr(USART_TypeDef* USARTx , uint8_t * Data , uint16_t len){
  uint16_t i = 0;
  while(i < len){
    if(Data[i] == 0xc0 ) // FEND
    {
      USART_SendData(  USARTx , 0xdb );
      USART_SendData(  USARTx , 0xdc );
    }
    else if ( Data[i] == 0xdb )  //FESC
    {
      USART_SendData(  USARTx , 0xdb );
      USART_SendData(  USARTx , 0xdd );
    }
    else
        USART_SendData(  USARTx , Data[i] );
    i++;
  }
}

uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{

  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

void USART_DMAEn(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{


  if (NewState != DISABLE)
  {
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    USARTx->CR3 &= (uint16_t)~USART_DMAReq;
  }
}




FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;    
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  itmask = USART_IT & IT_MASK;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01)
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) 
  {
    itmask &= USARTx->CR2;
  }
  else 
  {
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->SR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return bitstatus;  
}
