#ifndef __SSP_FUNCS_H_
#define __SSP_FUNCS_H_

#include "main.h"
void ping(Frame_t * Framein , Frame_t * Frameout);
void init(Frame_t * Framein , Frame_t * Frameout);
void ack(Frame_t * Framein , Frame_t * Frameout);
void nack(Frame_t * Framein , Frame_t * Frameout);
void get(Frame_t * Framein , Frame_t * Frameout);
void put(Frame_t * Framein , Frame_t * Frameout);
void read(Frame_t * Framein , Frame_t * Frameout);
void write(Frame_t * Framein , Frame_t * Frameout);
void id(Frame_t * Framein , Frame_t * Frameout);
void RESERVED(Frame_t * Framein , Frame_t * Frameout);
void CUSTOM(Frame_t * Framein , Frame_t * Frameout);
void addrt(Frame_t * Framein , Frame_t * Frameout);
void delrt(Frame_t * Framein , Frame_t * Frameout);
void getrt(Frame_t * Framein , Frame_t * Frameout);

void getAngles(Frame_t * Framein , Frame_t * Frameout);
void getGyroData(Frame_t * Framein , Frame_t * Frameout);
void getMagnetoData(Frame_t * Framein , Frame_t * Frameout);
void getTempData(Frame_t * Framein , Frame_t * Frameout);
void getSSData(Frame_t * Framein , Frame_t * Frameout);
void getTelemetryData(Frame_t * Framein , Frame_t * Frameout);
void changeMotors(Frame_t * Framein , Frame_t * Frameout);
void getMotors(Frame_t * Framein , Frame_t * Frameout);

void flashWrite(Frame_t * Framein , Frame_t * Frameout);
void flashRead(Frame_t * Framein , Frame_t * Frameout);
void FlashErase(Frame_t * Framein , Frame_t * Frameout);
void Flashunlock(Frame_t * Framein , Frame_t * Frameout);
void Flashlock(Frame_t * Framein , Frame_t * Frameout);
void ReadLog(Frame_t * Framein , Frame_t * Frameout);
#endif