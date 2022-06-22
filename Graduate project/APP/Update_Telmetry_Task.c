#include "APP.h"
extern Telemetry_t 	SensorsData;
#define UPDATE_DELAYMS 10
void vUpdate_Telmetry_Task( void * pvParameters )
{
	uint16_t ADC_readings[5]={0};
	int temperature_counter=0;
	for(;;)
	{
		xSemaphoreTake( SensorsData.DataMutex,portMAX_DELAY);
		ADC_myStart(ADC1);
		GYRO_Read(SensorsData.Gyros);
		for(uint8_t i = 0;i<3;i++)
		{
			 SensorsData.Angles[i] += (SensorsData.Gyros[i] * UPDATE_DELAYMS/1000);
		}
		MAGNETO_Read(SensorsData.Magnetos);
		if(temperature_counter>=500){
			SensorsData.temperature=Temp_Read();
			temperature_counter=0;
		}
		ADC_myRead(ADC1 ,ADC_readings);
		for(uint8_t i = 0;i<5;i++)
		{
			SensorsData.SS[i] = (float)ADC_readings[i] * 3.3 / (float)4096; // turn the ADC to float 
		}
		xSemaphoreGive( SensorsData.DataMutex );
		temperature_counter++;
		vTaskDelay(pdMS_TO_TICKS(UPDATE_DELAYMS));
	}
}