/**
* @file    main.c
* @author  Mostafa ElFallal
* @date    04-November-2021
* @brief   Main program body
*/
#include "main.h"
#include "APP.h"
QueueHandle_t  	FramesQueue; // used by ISR to receive new frames
QueueHandle_t  	ReceivedFramesQueue; // used by ISR to rstore the received frames
QueueHandle_t  	TransmittedFramesQueue;  // storage of frames that will be tranmitted
QueueHandle_t  	SavedFramesQueue;         // storage of frames that will be saved a
TaskHandle_t	Latch_Handle;
Telemetry_t 	SensorsData;
DevInfo_t		SensorsInfo;
int main(void)
{
	FramesQueue 			= xQueueCreate(10 , sizeof(Frame_t*)); 
	ReceivedFramesQueue 	= xQueueCreate(10 , sizeof(Frame_t*));
	TransmittedFramesQueue = xQueueCreate(10 , sizeof(Frame_t*));
	SavedFramesQueue 		= xQueueCreate(20 , sizeof(Frame_t*));
	SensorsData.DataMutex 	= xSemaphoreCreateMutex();
	latchvar.LatchMutex 	= xSemaphoreCreateMutex();
	xTaskCreate(vFrame_Provider_Task 	,"Task1",300,NULL,2,NULL);
	xTaskCreate(vLog_Saver_Task 		,"Task2",300,NULL,2,NULL);
	xTaskCreate(vReceiver_Task 			,"Task3",300,NULL,2,NULL);
	xTaskCreate(vTransmitter_Task 		,"Task4",300,NULL,2,NULL);
	xTaskCreate(vUpdate_Telmetry_Task 	,"Task5",300,NULL,2,NULL);
	xTaskCreate(vLatch_Task 			,"Task6",300,NULL,3,&Latch_Handle);
	APP_init();
	vTaskSuspend(Latch_Handle);
	vTaskStartScheduler();
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