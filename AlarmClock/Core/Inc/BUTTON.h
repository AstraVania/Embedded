#pragma once

#include "main.h"
#ifndef __BUTTON_H
#define __BUTTON_H

typedef enum Press
{
	Undefined,
	STATE_SHORT,
	STATE_LONG,
	STATE_DOUBLE,
}ButtonState;

typedef struct button
{
	GPIO_TypeDef*  GPIOx;
	uint16_t GPIO_Pin;
	int timeCounter;
	ButtonState state;
	int click;
	int timeFromClickToClick;
}Button;


void presseState(Button* button ,int timeAfterclick);

void buttonInit(Button* B , GPIO_TypeDef*  GPIOx , uint16_t GPIO_Pin);

void printClick(ButtonState STATE);

ButtonState getButtonState();

void resetButtonState();

void onButtonPeriodicEvent();

#endif /* INC_BUTTON_H_ */
