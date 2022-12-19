
#include "main.h"
#include "MyMain.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include"MainTimer.h"
#include "CLOCK.h"

void onClockPeriodicEvent(void * obj)
{
	Clock * clock = (Clock *)obj;
    clock->counter++;
}

void clockInit(Clock * TIM, TIM_HandleTypeDef * timer , uint32_t  autoreload )
{
	TIM->timer = timer;
	TIM->counter = 0;
	TIM->load = autoreload;
	HAL_TIM_Base_Stop(TIM->timer);
	__HAL_TIM_SET_AUTORELOAD(TIM->timer, TIM->load);  ///10
	HAL_TIM_Base_Start_IT(TIM->timer);
	MainTimer_registerCallbck(onClockPeriodicEvent , TIM);
}

void getTime(Clock * TIM)
{

	uint32_t tempTime = TIM->counter/1000;
	uint8_t remainder = tempTime % 3600;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
    hour = (tempTime - remainder) / 3600;
    min = (remainder - remainder % 60)/60;
    sec = remainder % 60;
    printf("The Time Now %02d:%02d:%02d \r\n" ,hour ,min ,sec);
}
