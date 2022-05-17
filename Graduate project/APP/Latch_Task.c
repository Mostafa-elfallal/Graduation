#include "APP.h"
extern QueueHandle_t  ReceivedFramesQueue;
#define LATCH_DELAYMS 50
void vLatch_Task( void * pvParameters )
{
	for(;;){
		xSemaphoreTake(latchvar.LatchMutex,portMAX_DELAY);
		if(Latch_isset())
		{
			Frame_t * pLatchedFrame =  pvPortMalloc(sizeof(Frame_t));
			*pLatchedFrame =   latchvar.LatchedFrame;
			xQueueSend(ReceivedFramesQueue,&pLatchedFrame,portMAX_DELAY);
		}
		xSemaphoreGive(latchvar.LatchMutex);
		vTaskDelay(pdMS_TO_TICKS(LATCH_DELAYMS));
	}
}