#include "main.h"

static uint8_t rear = 0;
static uint16_t size = 0;
extern QueueHandle_t  TransmittedFramesQueue;
Frame_t *ptempFrame;
static uint8_t getIndexStart(uint8_t  numOfFrames)
{
	 if( numOfFrames > rear)
	 {
		 return (255-(numOfFrames-rear));
	 }                                     
	 else
	 {
		return  (rear - numOfFrames); 
	 }
}
static void FrameGet(uint8_t index)
{
	MRAM_readBuffer(128*index,&ptempFrame->datacnt,1);
	MRAM_readBuffer(128*index+1,ptempFrame->data,ptempFrame->datacnt);
	
}
void FrameStore(Frame_t * frame)
{
	MRAM_writeBuffer(128*rear, &frame->datacnt ,1);
	MRAM_writeBuffer((128*rear)+1, frame->data ,frame->datacnt);
	rear++;          // will automatically overflow
	if(size < 256)
		size ++;
}
void FrameLoad(uint16_t numOfFrames)
{
	if ( numOfFrames == 0 || numOfFrames > size)
	{
		// read all frames  -- > 256 frame
		numOfFrames = size;
	}
	Frame_t * pFrameOut;
	pFrameOut =  pvPortMalloc(sizeof(Frame_t));
	FRAME_flush(pFrameOut);   // ensure it's ready
	FRAME_put(pFrameOut , OBC_ADDRESS);     
	FRAME_put(pFrameOut , ADCS_ADDRESS);    
	FRAME_put(pFrameOut , 22);
	FRAME_put(pFrameOut , numOfFrames-1);
	xQueueSend(TransmittedFramesQueue,&pFrameOut,portMAX_DELAY);
	uint8_t startindex = getIndexStart(numOfFrames);
	for(uint16_t i = 0;i<numOfFrames;i++)
	{
		ptempFrame=pvPortMalloc(sizeof(Frame_t));
		FrameGet(startindex+i);
		xQueueSend(TransmittedFramesQueue,&ptempFrame,portMAX_DELAY);
	}
	
}
