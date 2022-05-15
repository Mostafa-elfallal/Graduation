#include "TMR.h"
#include "RCC.h"

#define MOTOR1  0x01
#define MOTOR2  0x02
#define MOTOR3  0x03
#define PERIOD_TICKS 8399
void TMR_setPWM(uint8_t *motors)
{
	// three motors 
	/*    1 at A0 & A1        TIM5
	2 at B0 & B1        TIM3
	3 at D12 & D13      TIM4
	channel 1 = A0 and B0 and D12
	channel 2 = A1 and B1 and D13
	speed : 0 to 100
	*/
	uint8_t dir[3],speed[3];
	for (uint8_t i = 0;i<3;i++)
	{
		dir[i] = motors[i] >> 7;
		speed[i] = motors[i] & (~(1<<7));
		
	}
	if(dir[0] == 0)
	{
		//channel 2 off
		TIM5->CCR2 = 0;
		//channel 1 on with speed
		TIM5->CCR1 = (((PERIOD_TICKS + 1)*speed[0])/100);
	}
	else
	{
		// channel 1 off
		TIM5->CCR1 = 0;
		//channel 2 on with speed
		TIM5->CCR2 = (((PERIOD_TICKS + 1)*speed[0])/100);
	}
	TIM5->CCMR1 |= (TIM_OCPreload_Enable | (TIM_OCPreload_Enable<<8));
	if(dir[1] == 0)
	{
		//channel 2 off
		TIM3->CCR4 = 0;
		//channel 1 on with speed
		TIM3->CCR3 = (((PERIOD_TICKS + 1)*speed[1])/100); 
	}
	else
	{
		//channel 1 off
		TIM3->CCR3 = 0;
		//channel 2 on with speed
		TIM3->CCR4 = (((PERIOD_TICKS + 1)*speed[1])/100);
	}
	TIM3->CCMR2 |= (TIM_OCPreload_Enable | (uint16_t)(TIM_OCPreload_Enable << 8));
	if(dir[2] == 0)
	{
		//channel 2 off
		TIM4->CCR2 = 0;
		//channel 1 on with speed
		TIM4->CCR1 = (((PERIOD_TICKS + 1)*speed[2])/100);
	}
	else
	{
		// channel 1 off
		TIM4->CCR1 = 0;
		//channel 2 on with speed
		TIM4->CCR2 = (((PERIOD_TICKS + 1)*speed[2])/100);
	}
	TIM4->CCMR1 |= (TIM_OCPreload_Enable | (TIM_OCPreload_Enable<<8));
}
void TMR_myInit(void)
{
  TIM3->ARR = PERIOD_TICKS ;/* 10kHz PWM */
  TIM3->PSC = 0; 
  TIM3->EGR = TIM_PSCReloadMode_Immediate;
  TIM4->ARR = PERIOD_TICKS ;
  TIM4->PSC = 0; 
  TIM4->EGR = TIM_PSCReloadMode_Immediate;
  TIM5->ARR = PERIOD_TICKS ;
  TIM5->PSC = 0; 
  TIM5->EGR = TIM_PSCReloadMode_Immediate;
  /*********************************************************************/
  /* Start count on TIM4 */
  TIM4->CR1 |= TIM_CR1_CEN;
  /* Start count on TIM3 */
  TIM3->CR1 |= TIM_CR1_CEN;
  /* Start count on TIM5 */
  TIM5->CR1 |= TIM_CR1_CEN;
  
  TIM4->CCR2 = 0;
  TIM4->CCMR1 |= (TIM_OCMode_PWM2 | (TIM_OCMode_PWM2<<8));
  TIM4->CCR1 = 0;
  TIM4->CCER |= (TIM_OCPolarity_Low | (TIM_OCPolarity_Low<<4) |
                 TIM_OutputState_Enable |(TIM_OutputState_Enable << 4));
  TIM4->CCMR1 |= (TIM_OCPreload_Enable | (TIM_OCPreload_Enable<<8));
  TIM3->CCMR2 |= (TIM_OCMode_PWM2 | (uint16_t)(TIM_OCMode_PWM2 << 8));
  TIM3->CCR3 = 0;
  TIM3->CCR4 = 0;
  TIM3->CCER |= ( (uint16_t)(TIM_OCPolarity_Low << 8) |
                  (uint16_t)(TIM_OutputState_Enable << 8) |
                    (uint16_t)(TIM_OCPolarity_Low << 12)   |
                     (uint16_t)(TIM_OutputState_Enable << 12) );
  TIM3->CCMR2 |= (TIM_OCPreload_Enable | (uint16_t)(TIM_OCPreload_Enable << 8));
  //timer 5
  TIM5->CCR2 = 0;
  TIM5->CCMR1 |= (TIM_OCMode_PWM2 | (TIM_OCMode_PWM2<<8));
  TIM5->CCR1 = 0;
  TIM5->CCER |= (TIM_OCPolarity_Low | (TIM_OCPolarity_Low<<4) |
                 TIM_OutputState_Enable |(TIM_OutputState_Enable << 4));
  TIM5->CCMR1 |= (TIM_OCPreload_Enable | (uint16_t)(TIM_OCPreload_Enable << 8));
}