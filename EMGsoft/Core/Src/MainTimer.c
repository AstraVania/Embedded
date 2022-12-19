
#include<stdlib.h>
#include "main.h"
#include "MainTimer.h"

#define NUMBER_OF_TIMERS 10

typedef struct onTimer
{
	HandlerTime function;
	void * funcobj;
}TIMER;

int _timerPlaceInArr = 0;
TIMER _timeArr[10];


void MainTimer_registerCallbck(HandlerTime func , void * obj)
{
	_timerPlaceInArr = 0;
    int temp;
	while(_timerPlaceInArr < NUMBER_OF_TIMERS)
	{
		if(_timeArr[_timerPlaceInArr].function == func && _timeArr[_timerPlaceInArr].funcobj == obj)
		{
			return;
		}
		if(_timeArr[_timerPlaceInArr].function == NULL && _timeArr[_timerPlaceInArr].funcobj == NULL)
		{
			temp = _timerPlaceInArr;
		}
		_timerPlaceInArr++;
	}
	_timeArr[temp].function =  func;
	_timeArr[temp].funcobj = obj;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	_timerPlaceInArr = 0;
	while(_timerPlaceInArr < NUMBER_OF_TIMERS)
	{
		if(_timeArr[_timerPlaceInArr].function != NULL)
		{
			_timeArr[_timerPlaceInArr].function(_timeArr[_timerPlaceInArr].funcobj);
		}
		_timerPlaceInArr++;
	}
}

void MainTimer_unregisterCallbck(HandlerTime func , void * obj)
{
	_timerPlaceInArr = 0;
	while(_timerPlaceInArr < NUMBER_OF_TIMERS)
		{
			if(_timeArr[_timerPlaceInArr].function == func && _timeArr[_timerPlaceInArr].funcobj == obj)
			{
				_timeArr[_timerPlaceInArr].function = NULL;
				_timeArr[_timerPlaceInArr].funcobj = NULL;
			}
			_timerPlaceInArr++;
		}
}
