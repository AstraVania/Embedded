#ifndef __BUZZER_H
#define __BUZZER_H

#pragma once
#include "main.h"

typedef enum BuzzerState_
{
	BUZ_STATE_OFF,
	BUZ_STATE_ON,
} BuzzerState;


typedef struct Buzzer_
{
	TIM_HandleTypeDef* pwmTimer;
	uint32_t channel;
	BuzzerState state;
	int noteIdx;
	int notesCount;
	const int * noteFreqs;
	uint32_t  noteLengths;
} Buzzer;

void buzzerInit(Buzzer *buzzer, TIM_HandleTypeDef *pwmTimer, uint32_t channel);

void music(Buzzer * buzzer);

void buzOff(Buzzer * buzzer);

void buzStart(Buzzer * buzzer);

//void buzzerInit(Buzzer * buzzer , TIM_HandleTypeDef* pwmTimer, uint32_t channel);

#endif
