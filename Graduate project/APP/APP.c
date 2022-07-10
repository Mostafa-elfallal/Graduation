/**
  ******************************************************************************
  * @file    APP.c
  * @author  Mostafa ElFallal
  * @date    05-January-2022
  ******************************************************************************
*/
#include "App.h"
extern DevInfo_t		SensorsInfo;

void APP_FLASHPins(void)
{
  GPIO_InitTypeDef pins;
  pins.GPIO_Pin = MRAM_CS_PIN;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_Speed = GPIO_Speed_50MHz;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(MRAM_CS_PORT, &pins);
  pins.GPIO_Pin = FROM_CS_PIN;
  GPIO_Init(FROM_CS_PORT, &pins);
  pins.GPIO_Pin = FROM_WP_PIN | FROM_HOLD_PIN |MRAM_WP_PIN | MRAM_HOLD_PIN;
  GPIO_Init(FROM_WP_PORT, &pins);

}

void APP_TimerPins(void)
{
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
  
  GPIO_InitTypeDef pin;
  pin.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  pin.GPIO_OType = GPIO_OType_PP;
  pin.GPIO_PuPd = GPIO_PuPd_NOPULL;
  pin.GPIO_Mode = GPIO_Mode_AF;
  pin.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &pin);
  pin.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOA, &pin);
  GPIO_Init(GPIOB, &pin);
  TMR_myInit(); 
}
void APP_clockRun(void)
{
  //ADC
  RCC->APB2ENR |= RCC_APB2Periph_ADC1;
  //GPIOs
  RCC->AHB1ENR |= RCC_AHB1Periph_GPIOA;
  RCC->AHB1ENR |= RCC_AHB1Periph_GPIOB;
  RCC->AHB1ENR |= RCC_AHB1Periph_GPIOC;
  RCC->AHB1ENR |= RCC_AHB1Periph_GPIOD;
  RCC->AHB1ENR |= RCC_AHB1Periph_GPIOG;
  RCC->AHB1ENR |= RCC_AHB1Periph_GPIOF;
  //UART
  RCC->APB2ENR |= RCC_APB2Periph_USART1;
  //I2C2
  RCC->APB1ENR |= RCC_APB1Periph_I2C2;
  //Timers
  RCC->APB1ENR |= RCC_APB1Periph_TIM3;
  RCC->APB1ENR |= RCC_APB1Periph_TIM4;
  RCC->APB1ENR |= RCC_APB1Periph_TIM5;
  //SPI2
  RCC->APB1ENR |= RCC_APB1Periph_SPI2;
}
void APP_I2CPins(void)
{
  GPIO_InitTypeDef pins;
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
  // Connect PB10 to  I2C2_SCL
  // Connect PB11 to  I2C2_SDA
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);
  // Initialization of bGPIOB
  pins.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  pins.GPIO_Mode = GPIO_Mode_AF;
  pins.GPIO_Speed = GPIO_Fast_Speed;
  pins.GPIO_OType = GPIO_OType_OD;
  pins.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &pins);
  I2C_myInit(I2C2);
}
void APP_SPIPins(void)
{
// SPI2_MISO = PB14
//  SPI2_MOSI = PB15
// SPI2_SCK = PB13
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2); //clock
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);  //miso
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);  //mosi
  GPIO_InitTypeDef pins;
  pins.GPIO_Mode  = GPIO_Mode_AF;
  pins.GPIO_Speed = GPIO_Speed_50MHz;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_PuPd  = GPIO_PuPd_DOWN;
  pins.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &pins);
  // WP , WP1 , HOLD , HOLD1
  pins.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_OType = GPIO_OType_OD;
  pins.GPIO_Speed = GPIO_Speed_50MHz;
  pins.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &pins);
  // CE
  pins.GPIO_Pin = GPIO_Pin_12;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_Speed = GPIO_Speed_50MHz;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &pins);
  // CS
  pins.GPIO_Pin = GPIO_Pin_4;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_Speed = GPIO_Speed_50MHz;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &pins);
  SPI_Init(SPI2);
}
void APP_ADCPins(void)
{
  /*ADC pins*/
  /* PA2 PA3 PA7 PC4 PC5 */
//don't connect PC5
  GPIO_InitTypeDef pins;
  pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7;
  pins.GPIO_Mode = GPIO_Mode_AN;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&pins);
  pins.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
  GPIO_Init(GPIOC,&pins);
  ADC_myInit(ADC1);
}
void APP_ledsPins(void)
{
  GPIO_InitTypeDef pins;
  pins.GPIO_Pin = USER_BLUELED | USER_GREENLED | USER_ORANGELED | USER_REDLED;
  pins.GPIO_Mode = GPIO_Mode_OUT;
  pins.GPIO_OType = GPIO_OType_PP;
  pins.GPIO_PuPd = GPIO_PuPd_NOPULL;
  pins.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOD,&pins);
}
void APP_UARTPins(void)
{
  GPIO_InitTypeDef pins;
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
  //USART config
  USART_myInit(USART1);
}
void APP_init(void){
  APP_clockRun();
  APP_FLASHPins();

  FLASH_init();
  
  //init leds
  //APP_ledsPins();
  APP_ADCPins();
  //USART1 
  APP_UARTPins();
  // I2C
  APP_I2CPins();
//    RCC_ClocksTypeDef x;
//  RCC_GetClocksFreq(&x);
//  uint8_t z=0;
//  I2C_myTransmit(I2C2,0x48,&z,1);
  // TIMERS
  APP_TimerPins(); 
  //SPI 
  APP_SPIPins();
  MAGNETO_init();
  SensorsInfo.Magneto_WIA = MAGNETO_read_WIA();
  Temp_init();
  GYRO_init();
  SensorsInfo.Gyro_WIA = GYRO_read_WIA();
  MRAM_init();
  FROM_init();
  //enable
  __enable_irq();
}
/*

void APP_processIN(void)
{
  static uint8_t frameIndex = 0; // current index being processed 
  Frame_t * pFrame = FIFO_getCurrent(&FIFO_IN,frameIndex); // get the upcoming frame
  if( !FRAME_checkState(pFrame,sFRAME_RECEIVED))
  {
    // Frame isn't received completely yet, so just leave it alone 
    return;
  }
  // reaching here means it's a completed frame so let's do some checks
  if(! FRAME_lengthCheck(pFrame))
  {
    FRAME_putError(pFrame,eFRAME_SHORT);
  }
  // frame is long enough
  //let's calculate CRC
  uint16_t CRCval = FRAME_CRCCalc(pFrame,2);
  if(! (FRAME_CRCCmp(pFrame ,CRCval)))
  {
    // CRC ERROR 
    FRAME_putError(pFrame,eFRAME_CRCERROR);
  }
  // let's check type then 
  if(! (FRAME_typeCheck(pFrame)))
  {
    // Type ERROR 
    FRAME_putError(pFrame,eFRAME_TYPEERROR);
  }
  FRAME_changeState(pFrame,sFRAME_CHECKED);
  frameIndex = (frameIndex+1) % FIFO_CAPACITY;
}
void APP_processOUT(void)
{
  static uint8_t frameIndex = 0; // current index being processed 
  Frame_t * pFrame = FIFO_getCurrent(&FIFO_OUT,frameIndex); // get the upcoming frame
  if( !(FRAME_checkState(pFrame,sFRAME_EXECUTED) ) )
  {
    // Frame isn't completed yet , so just leave it alone 
    return;
  }
  if( FRAME_checkError(pFrame , eFRAME_DONOTHING))
  {
    // here we received a frame which we shouldn't reply to 
    
  }
  else
  {
    //let's calculate CRC
    uint16_t CRCval = FRAME_CRCCalc(pFrame,0);
    FRAME_CRCSet(pFrame, CRCval);
    FRAME_changeState(pFrame,sFRAME_CRCSET);
  }
  frameIndex = (frameIndex+1) % FIFO_CAPACITY;
}
void APP_execute(void)
{
  Frame_t * pFrameIn = FIFO_getCurrent(&FIFO_IN,FIFO_IN.front); // get the upcoming frame
  if( !(FRAME_checkState(pFrameIn,sFRAME_CHECKED) ))
  {
    // Frame isn't checked yet , so just leave it alone 
    return;
  }
  Frame_t * pFrameOut = FIFO_getCurrent(&FIFO_OUT,FIFO_OUT.rear); // get the upcoming frame 
  // we need to keep track on which frame we need to insert into 
  FRAME_flush(pFrameOut);   // ensure it's ready
  FRAME_put(pFrameOut , OBC_ADDRESS);     // put the dest
  FRAME_put(pFrameOut , ADCS_ADDRESS);    // put the src
  FRAME_put(pFrameOut , pFrameIn->data[TYPE]);   // put type but ping can change it 
  
  if(FRAME_checkError(pFrameIn,eFRAME_SHORT))
  {
    // Frame is short , discard
    
  }
  else if( FRAME_checkError(pFrameIn,eFRAME_CRCERROR ))
  {
    // Frame CRC is wrong , what to do ? 
    // discard for now
  }
  else if( FRAME_checkError(pFrameIn,eFRAME_TYPEERROR ))
  {
    // Frame type isn't defined in system , what to do ? 
    // discard for now
  }
  else {
    // it has been a long journey xD 
    // let's do execute the command 
    uint8_t type = pFrameIn->data[TYPE];
    FRAME_typeCall(type,pFrameIn,pFrameOut);     // call the received type with the place to put data in
    FRAME_changeState(pFrameOut,sFRAME_EXECUTED);
    FIFO_enqueue(&FIFO_OUT);                  // include pFrameOut in FIFO
  }
  FIFO_dequeue(&FIFO_IN); // exclude the completed command
}
void APP_Reply(void)
{
  Frame_t * pFrame = FIFO_getCurrent(&FIFO_OUT,FIFO_OUT.front); // get the upcoming frame
  if(! (FRAME_checkError(pFrame , eFRAME_DONOTHING))){  
    if(! (FRAME_checkState(pFrame,sFRAME_CRCSET )))
    {
      return;
    }
    FRAME_send(pFrame);
  }
     FIFO_dequeue(&FIFO_OUT);
}
	 */