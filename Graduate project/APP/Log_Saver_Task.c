#include "APP.h"
extern QueueHandle_t  SavedFramesQueue;
void vLog_Saver_Task( void * pvParameters )
{
	Frame_t * pFrame;
	for(;;)
	{
		xQueueReceive( SavedFramesQueue,&pFrame,portMAX_DELAY);
		//save Frame
		vPortFree(pFrame);
	}
}