/**
  * @file    main.c
  * @author  Mostafa ElFallal
  * @date    04-November-2021
  * @brief   Main program body
  */
#include "main.h"

int main(void)
{
  //clock enable for GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  //UART Clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  //init leds
  GPIO_InitTypeDef pins;
  pins.GPIO_Pin = USER_BLUELED | USER_GREENLED | USER_ORANGELED | USER_REDLED;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  pins.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOD,&pins);
  //USART1 PINS
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  // Connect PB6 to USART1_Tx

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
  // Connect PB7 to USART1_Rx
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
  // Initialization of GPIOA
  pins.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  pins.GPIO_Mode = GPIO_Mode_AF;
  pins.GPIO_Speed = GPIO_Fast_Speed;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &pins);

  //init USART1
  
  USART_InitTypeDef UARTconf;
  UARTconf.USART_BaudRate = 9600;
  UARTconf.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  UARTconf.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
  UARTconf.USART_Parity = USART_Parity_No;
  UARTconf.USART_StopBits = USART_StopBits_1;
  UARTconf.USART_WordLength = USART_WordLength_8b;
  USART_OverSampling8En(USART1,ENABLE);
  USART_Init(USART1, &UARTconf);
  NVIC_EnableIRQ(USART1_IRQn);
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  USART_En(USART1, ENABLE);
  //enable
  __enable_irq();
  while(1){
    Bus_Listen();
  }
 }

void assert_failed(uint8_t* file, uint32_t line)
{

  while (1)
  {
  }
}