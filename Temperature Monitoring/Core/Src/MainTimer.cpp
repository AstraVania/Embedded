
#include <MainTimer.h>
#include "TimerTask.h"


MainTimer::~MainTimer() {
	// TODO Auto-generated destructor stub
}


void MainTimer :: MainTimer_registerCallbck(TimerTask * time)
{
	int timerPlaceInArr = 0;
	while(timerPlaceInArr < numberOftimers)
	{
		if(_timeArr[timerPlaceInArr] == time)
		{
			return;
		}

		timerPlaceInArr++;
	}
	_timeArr[numberOftimers] = time;
	numberOftimers++;
}

void MainTimer :: MainTimer_unregisterCallbck(TimerTask * time)
{
	int timerPlaceInArr = 0;
	while(timerPlaceInArr < numberOftimers)
	{
		if(_timeArr[timerPlaceInArr] == time)
		{
			_timeArr[timerPlaceInArr] = nullptr;
			numberOftimers--;//NOT GOOD WAY
			return;
		}
		timerPlaceInArr++;
	}
}

void MainTimer ::MainTimer_Start()
{
	HAL_TIM_Base_Start_IT(timer);
}

void MainTimer::onInterrupt()
{
	for(int timerPlaceInArr = 0 ; timerPlaceInArr < numberOftimers; timerPlaceInArr++ )
	{
		if(_timeArr[timerPlaceInArr] != nullptr) //add if its on or off
		{
			_timeArr[timerPlaceInArr]->timerFunc();
		}
	}
}
