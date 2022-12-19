

#include "BUZZER.h"
#include "main.h"
#include "MainTimer.h"


#define OFF 0
#define FIREST_NOTE 0
int _notes[] = {381,361,340,322,303,287,270,255,241,216,340};


void buzzerInit(Buzzer * buzzer , TIM_HandleTypeDef* pwmTimer, uint32_t channel)
{
	    HAL_NVIC_EnableIRQ(TIM3_IRQn);
		buzzer->pwmTimer = pwmTimer;
		buzzer->channel = channel;
		buzzer->state = BUZ_STATE_OFF;
		buzzer->noteIdx = 0;
		buzzer->notesCount = sizeof(_notes) / sizeof(_notes[0]);
		buzzer->noteFreqs = _notes;
		buzzer->noteLengths = 0;

}

void music(Buzzer * buzzer)
{
   if((buzzer->noteLengths)%250==0)
   {
	   (buzzer->noteIdx)++;
	   if(buzzer->noteIdx == buzzer->notesCount)
	   {
		   buzzer->noteIdx = FIREST_NOTE;
	   }
   }
   __HAL_TIM_SET_COMPARE(buzzer->pwmTimer, buzzer->channel, OFF);
   __HAL_TIM_SET_AUTORELOAD(buzzer->pwmTimer, buzzer->noteFreqs[buzzer->noteIdx]);
   __HAL_TIM_SET_COMPARE(buzzer->pwmTimer, buzzer->channel, buzzer->noteFreqs[buzzer->noteIdx]/2);
}

void onBuzPeriodicEvent(void * obj)
{
	Buzzer * buzzer = (Buzzer *)obj;
    (buzzer->noteLengths)++;
	music((buzzer));
}

void buzOff(Buzzer * buzzer)
{
	if(buzzer->state == BUZ_STATE_OFF)
	{
			return;
	}
	HAL_TIM_Base_Stop((buzzer->pwmTimer));
	HAL_TIM_PWM_Stop((buzzer->pwmTimer), buzzer->channel);
	MainTimer_unregisterCallbck(onBuzPeriodicEvent , buzzer);
	buzzer->state = BUZ_STATE_OFF;
}

void buzStart(Buzzer * buzzer)
{
	if(buzzer->state == BUZ_STATE_ON)
	{
		return;
	}
	HAL_TIM_Base_Start((buzzer->pwmTimer));
	HAL_TIM_PWM_Start((buzzer->pwmTimer), buzzer->channel);
	MainTimer_registerCallbck(onBuzPeriodicEvent ,buzzer);
	buzzer->state = BUZ_STATE_ON;
}

