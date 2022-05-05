#include "main.h"

void queuefloat(Frame_t * Frame,uint8_t * data)
{
  for(uint8_t i = 0;i<4;i++)
  {
    FRAME_put(Frame,data[i]);
  }
  
}

void ping (Frame_t * Framein , Frame_t * Frameout)
{
  // respond with ACK
  // change the ype
  Frameout->data[TYPE] = ACK;
  
}
void init (Frame_t * Framein , Frame_t * Frameout)
{
  // respond with ACK 
  ack(Framein,Frameout);
}
void ack (Frame_t * Framein , Frame_t * Frameout)
{
  FRAME_put(Frameout,ACK);
}
void nack (Frame_t * Framein , Frame_t * Frameout)
{
  
}
void get (Frame_t * Framein , Frame_t * Frameout){
  
  
}
void put (Frame_t * Framein , Frame_t * Frameout){
}
void read (Frame_t * Framein , Frame_t * Frameout){
}
void write (Frame_t * Framein , Frame_t * Frameout){
}
void id (Frame_t * Framein , Frame_t * Frameout){
}
void RESERVED (Frame_t * Framein , Frame_t * Frameout){
}
void CUSTOM (Frame_t * Framein , Frame_t * Frameout){
}
void addrt (Frame_t * Framein , Frame_t * Frameout){
}
void delrt (Frame_t * Framein , Frame_t * Frameout){
}
void getrt (Frame_t * Framein , Frame_t * Frameout){
}
void getGyroData(Frame_t * Framein , Frame_t * Frameout)
{
  float data[3]={0};
  GYRO_Read(data);
  for( uint8_t i = 0 ; i < 3 ; i++)
    queuefloat(Frameout , (uint8_t *)&(data[i]) );
}
void getMagnetoData(Frame_t * Framein , Frame_t * Frameout){
  float data[3]={0};
  MAGNETO_Read(data);
  for( uint8_t i = 0 ; i < 3 ; i++)
    queuefloat(Frameout , (uint8_t *)&(data[i]) );
}
void getTempData(Frame_t * Framein , Frame_t * Frameout){
  float data= Temp_Read();
  queuefloat(Frameout,(uint8_t *)&(data));   // queue it 
}
void getSSData(Frame_t * Framein , Frame_t * Frameout){
  // assuming this function is used to read the ADC channels
  // test this with matlab
  ADC_myStart(ADC1);
  uint16_t x[5]={0};
  ADC_myRead(ADC1 ,x);
  float ADCdata[5];
  for(uint8_t i = 0;i<5;i++)
  {
    ADCdata[i] = (float)x[i] * 3.3 / (float)4096; // turn the ADC to float
    queuefloat(Frameout,(uint8_t *)&(ADCdata[i]));   // queue it 
  }
}
void getTelemetryData(Frame_t * Framein , Frame_t * Frameout){
  getGyroData(Framein,Frameout);
  getMagnetoData(Framein,Frameout);
  getTempData(Framein,Frameout);
  getSSData(Framein,Frameout);
}
void changeMotors(Frame_t * Framein , Frame_t * Frameout){
  TMR_setPWM(Framein->data[3] , Framein->data[4] , Framein->data[5]);
  TMR_setPWM(Framein->data[6] , Framein->data[7] , Framein->data[8]);
  TMR_setPWM(Framein->data[9] , Framein->data[10] , Framein->data[11]);
  Frameout->data[TYPE] = ACK;
}
void flashWrite(Frame_t * Framein , Frame_t * Frameout)
{
  uint32_t address  = *(uint32_t*)&(Framein->data[3]);
  uint32_t data     = *(uint32_t*)&(Framein->data[7]);
  FLASH_writeWord(address , data);
  Frameout->data[TYPE] = ACK;
}
void flashRead(Frame_t * Framein , Frame_t * Frameout)
{
  uint32_t address  = *(uint32_t*)&(Framein->data[3]);
  uint32_t data     = FLASH_readWord(address);
  queuefloat(Frameout,(uint8_t *)&(data));
}
void FlashErase(Frame_t * Framein , Frame_t * Frameout)
{
  FLASH_sectorErase(Framein->data[3]);
  Frameout->data[TYPE] = ACK;
}
void Flashunlock(Frame_t * Framein , Frame_t * Frameout){
    FLASH_unlock();
    Frameout->data[TYPE] = ACK;
}
void Flashlock(Frame_t * Framein , Frame_t * Frameout){
  FLASH_lock();
    Frameout->data[TYPE] = ACK;
}