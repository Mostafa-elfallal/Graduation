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

//Tasks 
void vFrame_Provider_Task( void * pvParameters );
void vLog_Saver_Task( void * pvParameters );
void vReceiver_Task( void * pvParameters );
void vTransmitter_Task( void * pvParameters );

void APP_processIN(void);
void APP_init(void);
void APP_processOUT(void);
void APP_execute(void);
void APP_Reply(void);
#endif