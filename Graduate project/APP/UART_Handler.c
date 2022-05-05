#include "App.h"
extern QueueHandle_t  FramesQueue;
extern QueueHandle_t  ReceivedFramesQueue;
Frame_t * pFrame = NULL; // Temp storage
void USART1_IRQHandler(void)
{
	static uint8_t isthisme = 0;
	/* * * * * * * * * * * * * * * * * * * * * * * * * *
	* 0 --> waiting for dest
	* 1 --> is this OBC ?
	* 2 --> not me or not OBC
	* 3 --> this is me 
	* 4 --> found FESC
	* * * * * * * * * * * * * * * * * * * * * * * * * */
	if(pFrame == NULL)
		xQueueReceiveFromISR( FramesQueue ,  &pFrame , NULL); // get frame
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{   // recieved data ?
		volatile uint8_t c =USART_ReceiveData(USART1);       // capature
		if(c == FEND && isthisme)
		{
			// this is ending FEND 
			// complete the frame and enqueue it
			if( isthisme != 2)
			{
				xQueueSendFromISR(ReceivedFramesQueue,&pFrame,NULL);
				pFrame = NULL;
			}
			isthisme = 0;
			return;
		}
		switch (isthisme){
		  case 0:
			if(c == FEND)
			{
				// this is a flushing FEND
				FRAME_flush(pFrame);
				// Do nothing
			}
			else if(c == ADCS_ADDRESS){
				//yes that is me 
				isthisme = 1;
			}
			else{
				// no it's not me 
				isthisme = 2;
			}
			break;
		  case 1:
			// is that obc ?
			isthisme = (c == OBC_ADDRESS) ? 3 : 2;
			break;
		  case 2:
			FRAME_flush(pFrame);
			//not me or not OBC calling
			// don't do anything
			break;
		  case 3:
			// this call is from OBC and for me 
			isthisme = (c == 0xdB) ? 4 : isthisme;     // FESC check   
			break;
		  case 4:
			if( c == 0xdc ){
				//FESC TFEND
				c = 0xc0;
				isthisme = 3;
			}
			else if ( c == 0xdd ){
				//FESC TFESC
				c = 0xdb;
				isthisme = 3;
			}
			else 
				//  error 
				//  discard
				isthisme = 2;
			break;
		}
		if(isthisme == 1 || isthisme == 3 )
			FRAME_put(pFrame , c);
	}
}