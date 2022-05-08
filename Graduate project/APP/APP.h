/**
  ******************************************************************************
  * @file    APP.h
  * @author  Mostafa ElFallal
  * @date    05-January-2022
  ******************************************************************************
*/
#ifndef __APP__H_
#define __APP__H_
#include "main.h"

typedef struct 
{
	float Gyros[3];
	float Magnetos[3];
	float SS[5];
	float temperature;
	float Angles[3];
	SemaphoreHandle_t  DataMutex;
}Telemetry_t;
typedef struct
{
	uint8_t Gyro_WIA;
	uint8_t Magneto_WIA;
	int8_t Motors[3];
}DevInfo_t;
//Tasks 
void vFrame_Provider_Task( void * pvParameters );
void vLog_Saver_Task( void * pvParameters );
void vReceiver_Task( void * pvParameters );
void vTransmitter_Task( void * pvParameters );
void vUpdate_Telmetry_Task  ( void * pvParameters );
void APP_processIN(void);
void APP_init(void);
void APP_processOUT(void);
void APP_execute(void);
void APP_Reply(void);
#endif