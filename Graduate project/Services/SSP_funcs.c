#include "APP.h"
extern Telemetry_t 	SensorsData;
extern DevInfo_t	SensorsInfo;
extern TaskHandle_t	Latch_Handle;
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
void getAngles(Frame_t * Framein , Frame_t * Frameout)
{
	xSemaphoreTake(SensorsData.DataMutex,portMAX_DELAY);
	for( uint8_t i = 0 ; i < 3 ; i++){
		queuefloat(Frameout , (uint8_t *)&(SensorsData.Angles[i]) );
		SensorsData.Angles[i] = 0;
	}
	xSemaphoreGive( SensorsData.DataMutex);
}
void getGyroData(Frame_t * Framein , Frame_t * Frameout)
{
	/*
	float data[3]={0};
	GYRO_Read(data);
	for( uint8_t i = 0 ; i < 3 ; i++)
	queuefloat(Frameout , (uint8_t *)&(data[i]) );
	*/
	if(Framein->data[3] == 0xFF){
		//read who i am
		FRAME_put(Frameout,SensorsInfo.Gyro_WIA);
	}
	else
	{
		xSemaphoreTake(SensorsData.DataMutex,portMAX_DELAY);
		for( uint8_t i = 0 ; i < 3 ; i++)
			queuefloat(Frameout , (uint8_t *)&(SensorsData.Gyros[i]) );
		xSemaphoreGive( SensorsData.DataMutex);
	}
}
void getMagnetoData(Frame_t * Framein , Frame_t * Frameout){
	if(Framein->data[3] == 0xFF){
		//read who i am
		FRAME_put(Frameout,SensorsInfo.Magneto_WIA);
	}
	else
	{
	xSemaphoreTake(SensorsData.DataMutex,portMAX_DELAY);
	for( uint8_t i = 0 ; i < 3 ; i++)
		queuefloat(Frameout , (uint8_t *)&(SensorsData.Magnetos[i]) );
	xSemaphoreGive( SensorsData.DataMutex);
	}
	/*
  float data[3]={0};
  MAGNETO_Read(data);
  for( uint8_t i = 0 ; i < 3 ; i++)
    queuefloat(Frameout , (uint8_t *)&(data[i]) );
*/
}
void getTempData(Frame_t * Framein , Frame_t * Frameout){
	/*
  float data= Temp_Read();
  queuefloat(Frameout,(uint8_t *)&(data));   // queue it 
*/
	xSemaphoreTake(SensorsData.DataMutex,portMAX_DELAY);
		queuefloat(Frameout , (uint8_t *)&(SensorsData.temperature) );
	xSemaphoreGive( SensorsData.DataMutex);
}
void getSSData(Frame_t * Framein , Frame_t * Frameout){
	/*
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
*/
	xSemaphoreTake(SensorsData.DataMutex,portMAX_DELAY);
	for( uint8_t i = 0 ; i < 5 ; i++)
		queuefloat(Frameout , (uint8_t *)&(SensorsData.SS[i]) );
	xSemaphoreGive( SensorsData.DataMutex);
}
void getTelemetryData(Frame_t * Framein , Frame_t * Frameout){
  getGyroData(Framein,Frameout);
  getMagnetoData(Framein,Frameout);
  getTempData(Framein,Frameout);
  getSSData(Framein,Frameout);
  getAngles(Framein,Frameout);
}
void changeMotors(Frame_t * Framein , Frame_t * Frameout){
	TMR_setPWM(&(Framein->data[3]));
	for(uint8_t i = 0;i<3;i++)
	{
		SensorsInfo.Motors[i]= Framein->data[3+i];
	}
	Frameout->data[TYPE] = ACK;
}
void getMotors(Frame_t * Framein , Frame_t * Frameout){
	for( uint8_t i = 0;i<3;i++ )
	{
		FRAME_put(Frameout,SensorsInfo.Motors[i]);
	}
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
void ReadLog(Frame_t * Framein , Frame_t * Frameout)
{
	FrameLoad(Framein->data[3]);
}
void StartLatch(Frame_t * Framein , Frame_t * Frameout)
{
	xSemaphoreTake(latchvar.LatchMutex,portMAX_DELAY);
	Latch_changeSetting(0);
	Latch_changeLatching(1);
	xSemaphoreGive(latchvar.LatchMutex);
	vTaskResume(Latch_Handle);
}
void StopLatch(Frame_t * Framein , Frame_t * Frameout)
{
	xSemaphoreTake(latchvar.LatchMutex,portMAX_DELAY);
	Latch_changeSetting(0);
	Latch_changeLatching(0);
	xSemaphoreGive(latchvar.LatchMutex);
}