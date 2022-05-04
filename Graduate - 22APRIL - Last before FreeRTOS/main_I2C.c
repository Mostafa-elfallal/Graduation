/**
  * @file    main.c
  * @author  Mostafa ElFallal
  * @date    04-November-2021
  * @brief   Main program body
  */

#include "main.h"

void I2C1_Send_str(char * str){
    I2C_GenerateSTART(I2C1,ENABLE);
    while (I2C_SR1_SB  != (I2C_SR1_SB & I2C1->SR1)){
    }
    (void)I2C1->SR1;
    I2C_Send7bitAddress(I2C1,0x55<<1,I2C_Direction_Transmitter);
  /*  while(I2C_SR1_ADDR != (I2C_SR1_ADDR  & I2C1->SR1))
    {
    }*/
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    while(*str != '\0'){ 
    while( I2C_SR1_TXE != (I2C_SR1_TXE & I2C1->SR1))
    {
    }
    I2C_SendData(I2C1,*str);
    str++;
    }
    I2C_GenerateSTOP(I2C1,ENABLE);
}
void I2C2_EV_IRQHandler(void){
  if(I2C_SR1_ADDR == (I2C_SR1_ADDR  & I2C2->SR1)){
      //iam here
     (void)I2C2->SR1;
    (void)I2C2->SR2;
    }
    if(I2C_SR1_RXNE == (I2C_SR1_RXNE  & I2C2->SR1))
    {
      //heeey data
    char c = I2C_ReceiveData(I2C2);
    switch(c)
    {
    case 'b':
      //toggle blue led
      GPIO_ToggleBits(USER_BLUELED_PORT,USER_BLUELED);
      //USART_PutString("Toggling BLUE\n\r");
      break;
    case 'g':
      //toggle green
      GPIO_ToggleBits(USER_GREENLED_PORT,USER_GREENLED);
      //USART_PutString("Toggling GREEN\n\r");
      break;
    case 'r':
      //toggle red
      GPIO_ToggleBits(USER_REDLED_PORT,USER_REDLED);
      //USART_PutString("Toggling RED\n\r");
      break;
    case 'o':
      //toggle orange
      GPIO_ToggleBits(USER_ORANGELED_PORT,USER_ORANGELED);
     //USART_PutString("Toggling ORANGE\n\r");
      break;
    default :
      // turn all for 1 sec
    	GPIO_ToggleBits(USER_ORANGELED_PORT
                    , USER_BLUELED | USER_GREENLED | USER_REDLED | USER_ORANGELED);

        break;
      }
    }
    if(I2C_SR1_STOPF == (I2C_SR1_STOPF & I2C2->SR1))
    {
      (void)I2C2->SR1;
      I2C_ClearFlag(I2C2,I2C_SR1_STOPF);
    }
}
int main(void)
{
 //clock enable for GPIOD for LEDS
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
 //I2C Clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
  //init leds
  GPIO_InitTypeDef pins;
  pins.GPIO_Pin = USER_BLUELED | USER_GREENLED | USER_ORANGELED | USER_REDLED;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  pins.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOD,&pins);
  //I2C PINS        PB6 - PB7 - PB10 - PB11
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C1);
  // Initialization of GPIOA
  pins.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11;
  pins.GPIO_Mode = GPIO_Mode_AF;
  pins.GPIO_Speed = GPIO_Fast_Speed;
  pins.GPIO_OType = GPIO_OType_OD;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &pins);

  //init I2C1
  I2C_InitTypeDef I2Cconf;
  I2Cconf.I2C_Ack = I2C_Ack_Enable;
  I2Cconf.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2Cconf.I2C_ClockSpeed = 400000;
  I2Cconf.I2C_DutyCycle = I2C_DutyCycle_2;
  I2Cconf.I2C_OwnAddress1 = 0x55;
  I2C_Init(I2C2,&I2Cconf);
  I2Cconf.I2C_Ack = I2C_Ack_Disable;
  I2Cconf.I2C_OwnAddress1 = 0x15;
  I2C_Init(I2C1,&I2Cconf);
  //TO DO
  NVIC_SetPriorityGrouping(3);
  NVIC_SetPriority(I2C2_EV_IRQn, 1);
  NVIC_EnableIRQ(I2C1_EV_IRQn);
  I2C_ITConfig(I2C2,I2C_IT_BUF | I2C_IT_EVT,ENABLE);
  I2C_StretchClockEn(I2C1,ENABLE);
  I2C_StretchClockEn(I2C2,ENABLE);
  I2C_En(I2C1, ENABLE);
  I2C_En(I2C2, ENABLE);
  __enable_irq();
  char x[4]="bgro";
  while(1){
	I2C1_Send_str(x);
  for (volatile uint32_t i=0; i<10000000;i++)
            {
				;
            }
    }
 }

void assert_failed(uint8_t* file, uint32_t line)
{

  while (1)
  {
  }
}
