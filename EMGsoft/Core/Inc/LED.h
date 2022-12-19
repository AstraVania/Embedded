

#pragma once
#include<stdlib.h>
#include "main.h"


#ifndef __LED__H
#define __LED__H


typedef struct led
{
	GPIO_TypeDef*  GPIOx;
	uint16_t GPIO_Pin;
	int timeCounter;
	int maxPeriod;

}Led;


void ledControlBrightness(TIM_HandleTypeDef* pwmTimer ,uint32_t channel,int level);

void ledInit(Led* led , GPIO_TypeDef*  GPIOx , uint16_t GPIO_Pin);

void ledOff(Led * led);

void ledOn(Led * led);

void ledBlink(Led * led);

void ledOnTimerInterrupt(void * obj);

#endif
