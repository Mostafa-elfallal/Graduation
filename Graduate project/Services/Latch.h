#ifndef __LATCH_H_
#define __LATCH_H_


#include "main.h"

typedef struct {
	Frame_t LatchedFrame;
	uint8_t Latching;
	uint8_t Setting;
	SemaphoreHandle_t  LatchMutex;
}latch_t;
extern latch_t  latchvar;


uint8_t Latch_isset(void);
void  	Latch_changeSetting(uint8_t newsetting);
uint8_t Latch_isLatched(void);
void  	Latch_changeLatching(uint8_t newLatching);
void 	Latch_frame(Frame_t* pframe);
#endif