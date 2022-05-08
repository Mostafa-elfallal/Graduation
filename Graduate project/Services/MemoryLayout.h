#ifndef __MEMLAYOUT__H_
#define __MEMLAYOUT__H_
#include "main.h"

void FrameStore(Frame_t * frame);    // store this frame in MRAM
void FrameLoad(uint8_t numOfFrames);   // Load the last numOfFrames in transmitter task
#endif