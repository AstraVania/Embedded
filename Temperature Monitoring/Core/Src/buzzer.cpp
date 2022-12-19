/*
 * buzzer.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include <buzzer.h>
#include "MainTimer.h"
extern MainTimer * Timer;
#define OFF 0
#define FIREST_NOTE 0
int _notes[] = {381,361,340,322,303,287,270,255,241,216,340};


void buzzer::timerFunc()
{

    _noteLengths++;
    if((_noteLengths)%250==0)
       {
    	   _noteIdx++;
    	   if(_noteIdx == _notesCount)
    	   {
    		   _noteIdx = FIREST_NOTE;
    	   }
       }
       __HAL_TIM_SET_COMPARE(_pwmTimer, _channel, OFF);
       __HAL_TIM_SET_AUTORELOAD(_pwmTimer, _notes[_noteIdx]);
       __HAL_TIM_SET_COMPARE(_pwmTimer, _channel, _notes[_noteIdx]/2);
}

void buzzer::buzOff()
{
	if(_state == BUZ_STATE_OFF)
	{
			return;
	}
	HAL_TIM_Base_Stop((_pwmTimer));
	HAL_TIM_PWM_Stop((_pwmTimer), _channel);
	Timer->MainTimer_unregisterCallbck(this);
	_state = BUZ_STATE_OFF;
}

void buzzer::buzStart()
{
	if(_state == BUZ_STATE_ON)
	{
		return;
	}
	_notesCount = sizeof(_notes)/ sizeof(int);
	HAL_TIM_Base_Start((_pwmTimer));
	HAL_TIM_PWM_Start((_pwmTimer), _channel);
	Timer->MainTimer_registerCallbck(this);
	_state = BUZ_STATE_ON;
}
