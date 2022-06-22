#include "APP.h"
extern QueueHandle_t  ReceivedFramesQueue;
extern QueueHandle_t  TransmittedFramesQueue;
extern QueueHandle_t  SavedFramesQueue;
void vReceiver_Task( void * pvParameters )
{
	Frame_t * pFrame;
	Frame_t * pFrameOut;
	for(;;)
	{
		xQueueReceive( ReceivedFramesQueue,&pFrame,portMAX_DELAY);
		xSemaphoreTake(latchvar.LatchMutex,portMAX_DELAY);
		if(Latch_isLatched())
		{
			Latch_frame( pFrame);
			Latch_changeSetting(1);
		}
		xSemaphoreGive(latchvar.LatchMutex);
		pFrameOut =  pvPortMalloc(sizeof(Frame_t));
		FRAME_flush(pFrameOut);   // ensure it's ready
		FRAME_put(pFrameOut , OBC_ADDRESS);     // put the dest
		FRAME_put(pFrameOut , ADCS_ADDRESS);    // put the src
		FRAME_put(pFrameOut , pFrame->data[TYPE]);   // put type 
		if(! FRAME_lengthCheck(pFrame))
		{
			// frame is short
		}
		else
		{
			// frame is long enough
			//let's calculate CRC
			uint16_t CRCval = FRAME_CRCCalc(pFrame,2);
			if(! (FRAME_CRCCmp(pFrame ,CRCval)))
			{
				// CRC ERROR 
			}
			// let's check type then 
			else if(! (FRAME_typeCheck(pFrame)))
			{
				// Type ERROR
			}
			else
			{
				// it has been a long journey xD 
				// let's do execute the command 
				uint8_t type = pFrame->data[TYPE];
				FRAME_typeCall(type,pFrame,pFrameOut);     // call the received type with the place to put data in
				//put in to be stored and out to be transmitted
				xQueueSend(TransmittedFramesQueue,&pFrameOut,portMAX_DELAY);
				
			}
		}
		xQueueSend(SavedFramesQueue,&pFrame,portMAX_DELAY);
		
	}
}