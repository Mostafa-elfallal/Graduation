#include "main.h"
FIFO_t FIFO_IN;         // will be used as extern in other modules
FIFO_t FIFO_OUT;
void FIFO_init(FIFO_t * me)
{
    me->front = 0;
    me->size = 0;
    me->rear = 0;  // see enqueue
}

// Queue is full when size becomes
// equal to the capacity
uint8_t FIFO_isFull(FIFO_t* queue)
{
    return (queue->size == FIFO_CAPACITY);
}
// Queue is empty when size is 0
uint8_t FIFO_isEmpty(FIFO_t* queue)
{
    return (queue->size == 0);
}
// Function to increment 
// It changes rear and size
// you must check whether it is full or no 

void FIFO_enqueue(FIFO_t* queue)
{
  // virtually putting data in rear , but we actually put data before that using getCurrent
    queue->rear = (queue->rear + 1) % FIFO_CAPACITY;  // increment 
    queue->size = queue->size + 1;
}
// Function to decrement.
// It changes front and size
// you must check whether it is empty or no 
void FIFO_dequeue(FIFO_t* queue)
{
  //virtually retreving data from front 
    FRAME_flush(&(queue -> Frames[queue->front]));
    queue->front = (queue->front + 1) % FIFO_CAPACITY;
    queue->size = queue->size - 1;
}
//used to traverse the FIFO without queuing.
Frame_t * FIFO_getCurrent(FIFO_t* queue , uint8_t currentIndex)
{
 return &(queue->Frames[(currentIndex) % FIFO_CAPACITY]);
}

