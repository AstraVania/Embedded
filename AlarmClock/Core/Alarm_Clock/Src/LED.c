
#include<stdlib.h>
//#include<MainTimer.h>
#include "LED.h"
#include "main.h"


void ledInit(Led* led , GPIO_TypeDef*  GPIOx , uint16_t GPIO_Pin)
{
	led->GPIO_Pin = GPIO_Pin;
	led->GPIOx = GPIOx;
	led->timeCounter = 0;
}
void ledOff(Led * led)
{
	//MainTimer_unregisterCallbck(ledOnTimerInterrupt , led);
	led->maxPeriod = 0;
	HAL_GPIO_WritePin(led->GPIOx , led->GPIO_Pin, 0);
}
void ledOn(Led * led)
{
	led->maxPeriod = 0;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 1);
}

void ledBlink(Led * led)
{
	//MainTimer_registerCallbck(ledOnTimerInterrupt , led);
	led->maxPeriod = 500;
	led->timeCounter = 0;
}

//void ledControlBrightness(TIM_HandleTypeDef* pwmTimer ,uint32_t channel, int level)
//{
//	__HAL_TIM_SET_COMPARE(pwmTimer, channel, level);
//}

void ledOnTimerInterrupt(void * obj)
{
	Led * led = (Led *)obj;
	led->timeCounter++;
	if (led->timeCounter >= led->maxPeriod && led->maxPeriod > 0)
	{
		led->timeCounter = 0;
		HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
	}
}

