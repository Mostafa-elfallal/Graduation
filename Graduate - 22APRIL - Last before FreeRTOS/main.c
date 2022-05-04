/**
* @file    main.c
* @author  Mostafa ElFallal
* @date    04-November-2021
* @brief   Main program body
*/
#include "main.h"
#include "APP.h"
int main(void)
{
  APP_init();
  while(1){
    APP_processIN();
    APP_execute();
    APP_processOUT();
    APP_Reply();
  }
  //I2C2_APPmyIint();
  //MPU_readwhoIAM();
  //MPU_testReg();
  // while(1);
}

void assert_failed(uint8_t* file, uint32_t line)
{
  
  while (1)
  {
  }
}