#ifndef __SSP__H_
#define __SSP__H_

#include "main.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *          Defining the errors   & states of frame            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
typedef enum 
{
    eFRAME_RESET        =   0, 
    eFRAME_SHORT        =   1,
    eFRAME_CRCERROR     =   2,
    eFRAME_TYPEERROR    =   4,
    eFRAME_DONOTHING    =   8
}error_t;


/* * * * * * * * * * * * * * * * * * * * * * *
 *          Defining the element             *
 * * * * * * * * * * * * * * * * * * * * * * */
typedef struct
{
    error_t errorcode;
    uint8_t data[102];  // dest + src + type + data + CRC 
    uint8_t datacnt;
}Frame_t;

void        FRAME_put           (Frame_t * Frame , uint8_t item);
void        FRAME_completed     (Frame_t * Frame);
void        FRAME_flush         (Frame_t * Frame);
uint8_t     FRAME_lengthCheck   (Frame_t * Frame);
uint16_t    FRAME_CRCCalc       (Frame_t * me , uint8_t len);
uint8_t     FRAME_CRCCmp        (Frame_t* me,uint16_t crc);
uint8_t     FRAME_typeCheck     (Frame_t* me);
void        FRAME_typeCall      (uint8_t type ,  Frame_t* framein , Frame_t* frameout);
void        FRAME_CRCSet        (Frame_t* me,uint16_t crc);
void        FRAME_send          (Frame_t* me);
void        FRAME_putError      (Frame_t* me,error_t error);
uint8_t     FRAME_checkError    (Frame_t* me,error_t error);
#endif