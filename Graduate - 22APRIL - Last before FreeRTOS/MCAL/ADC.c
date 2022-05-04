/**
  ******************************************************************************
  * @file    ADC.c
  * @author  Mostafa ElFallal
  * @date    05-January-2022
  *******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "ADC.h"
#include "RCC.h"
void ADC_DeInit(void)
{
  /* Enable all ADCs reset state */
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, ENABLE);
  
  /* Release all ADCs from reset state */
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, DISABLE);
}
void ADC_myStart(ADC_TypeDef* ADCx){
  /*start injected*/
  ADCx->CR2 |= (uint32_t)ADC_CR2_JSWSTART;
  /*start regular*/
  ADCx->CR2 |= (uint32_t)ADC_CR2_SWSTART;
}
void ADC_myInit(ADC_TypeDef* ADCx)
{
    // we have 4 Injected and 1 regular channels.
  
  uint8_t INJECTED1 = ADC_Channel_2;
  uint8_t INJECTED2 = ADC_Channel_3;
  uint8_t INJECTED3 = ADC_Channel_7;
  uint8_t INJECTED4 = ADC_Channel_14;
  uint8_t REGULAR   = ADC_Channel_15;
  /* Scan mode */ 
  ADCx->CR1 = (1 << 8);
  /*only 1 regular Channel*/
  ADCx->SQR3 = REGULAR & 0x0F ;
  /* 4 Injected Channels */
  ADCx->JSQR |= (3 << 20);
  ADCx->JSQR |= (INJECTED1 << 0);
  ADCx->JSQR |= (INJECTED2 << 5);
  ADCx->JSQR |= (INJECTED3 << 10);
  ADCx->JSQR |= (INJECTED4 << 15);
    /*Enabl ADCx*/
  ADCx->CR2 = (1 << 0);
}
void ADC_myRead(ADC_TypeDef* ADCx , uint16_t *arr){
  /*wait for all channels to be converted*/
  while ((ADCx->SR & (ADC_FLAG_EOC | ADC_FLAG_JEOC)) != (ADC_FLAG_EOC | ADC_FLAG_JEOC));
  arr[0] =   (uint16_t)ADCx->JDR1;
  arr[1] =   (uint16_t)ADCx->JDR2;
  arr[2] =   (uint16_t)ADCx->JDR3;
  arr[3] =   (uint16_t)ADCx->JDR4;
  arr[4] =   (uint16_t)ADCx->DR;
}