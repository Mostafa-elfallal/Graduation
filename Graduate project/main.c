/**
* @file    main.c
* @author  Mostafa ElFallal
* @date    04-November-2021
* @brief   Main program body
*/
#include "main.h"
#include "APP.h"
QueueHandle_t  FramesQueue; // used by ISR to receive new frames
QueueHandle_t  ReceivedFramesQueue; // used by ISR to rstore the received frames
QueueHandle_t  TransmittedFramesQueue;  // storage of frames that will be tranmitted
QueueHandle_t  SavedFramesQueue;         // storage of frames that will be saved
int main(void)
{
	FramesQueue = xQueueCreate(10 , sizeof(Frame_t*)); 
	ReceivedFramesQueue = xQueueCreate(10 , sizeof(Frame_t*));
	TransmittedFramesQueue = xQueueCreate(10 , sizeof(Frame_t*));
	SavedFramesQueue = xQueueCreate(20 , sizeof(Frame_t*));
	xTaskCreate(vFrame_Provider_Task ,"Task1",1000,NULL,2,NULL);
	APP_init();
	while(1){
		/*
		APP_processIN();
		APP_execute();
		APP_processOUT();
		APP_Reply();
*/
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