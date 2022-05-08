#include "Latch.h"

latch_t  latchvar;
uint8_t Latch_isset(void)
{
	return latchvar.Setting;
}

void  	Latch_changeSetting(uint8_t newSetting)
{
	latchvar.Setting = newSetting;
}
uint8_t Latch_isLatched(void)
{
	return latchvar.Latching;
}
void  	Latch_changeLatching(uint8_t newLatching)
{
	latchvar.Latching = newLatching;
}
void 	Latch_frame(Frame_t* pframe)
{
	 latchvar.LatchedFrame =* pframe;
}