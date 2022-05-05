#include "APP.h"
extern QueueHandle_t  TransmittedFramesQueue;
void vTransmitter_Task( void * pvParameters )
{
	Frame_t * pFrame;
	for(;;)
	{
		xQueueReceive( TransmittedFramesQueue,&pFrame,portMAX_DELAY);
		if( FRAME_checkError(pFrame , eFRAME_DONOTHING))
		{
			// here we received a frame which we shouldn't reply to 
			
		}
		else
		{
			//let's calculate CRC
			uint16_t CRCval = FRAME_CRCCalc(pFrame,0);
			FRAME_CRCSet(pFrame, CRCval);
			FRAME_send(pFrame);
			vPortFree(pFrame);
		}
	}
}