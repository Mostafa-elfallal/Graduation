#ifndef __FIFO__H_
#define __FIFO__H_

#include "main.h"
#define FIFO_CAPACITY  100

/* * * * * * * * * * * * * * * * * * * * * * *
 *          Defining the FIFO                *
 * * * * * * * * * * * * * * * * * * * * * * */
typedef struct 
{
    Frame_t Frames[FIFO_CAPACITY];           // we can store up to 100 frames
    uint8_t front, rear, size;
} FIFO_t;

extern FIFO_t FIFO_IN;
extern FIFO_t FIFO_OUT;

/*
    used to clear the fifo and succeed if the pointer isn't NULL
*/
void FIFO_init(FIFO_t * me);

/*
    used to add the val to the fifo in the propriate place
    PRE : Fifo must be initialized and not full
*/
uint8_t FIFO_isFull(FIFO_t* queue);
/*
    used to extract the data into val pointer.
    PRE : Fifo must be initialized and not empty
*/
uint8_t FIFO_isEmpty(FIFO_t* queue);

void FIFO_enqueue(FIFO_t* queue);
void FIFO_dequeue(FIFO_t* queue);
Frame_t * FIFO_getCurrent(FIFO_t* queue , uint8_t currentIndex);

#endif