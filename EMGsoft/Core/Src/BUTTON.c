
#include "BUTTON.h"
#include "main.h"
#include "MyMain.h"
#include <stdio.h>
#include "MainTimer.h"

void onButtonPeriodicEvent(void* obj);


void buttonInit(Button* button , GPIO_TypeDef*  GPIOx , uint16_t GPIO_Pin)
{
	button->GPIO_Pin = GPIO_Pin;//pin
	button->GPIOx = GPIOx;//port
	button->state = Undefined;
	button->click = 0;
	button->timeFromClickToClick = 0;
}

void presseState(Button* button ,int timeAfterclick)
{
    if(timeAfterclick >= 500)
	{
    	button->state = STATE_LONG;
		printClick(button->state);
	}
	else if(timeAfterclick < 500)
	{
		button->state = Undefined;
		MainTimer_registerCallbck(onButtonPeriodicEvent, button);
		(button->click)++;
	}
}

void printClick(ButtonState newButtonState)
{

	switch (newButtonState)
	{
	 case STATE_SHORT :
		 	 	 	printf("ITS SHORT PRESS\n\r");
		 	 	 	break;
	 case STATE_LONG :
		            printf("ITS LONG PRESS\n\r");
		            break;

	 case STATE_DOUBLE :
		           printf("ITS DOUBLE PRESS\n\r");
		           break;
	 default :
	               break;
	}
}

ButtonState getButtonState(Button* button)
{
	return (button->state);
}

void resetButtonState(Button* button)
{
	(button->state = Undefined);
}

void onButtonPeriodicEvent(void * obj)
{
	Button* button = (Button*)obj;
	if(button->click >= 1)
	{
		(button->timeFromClickToClick)++;
		if (button->click == 2)
		{
			button->click = 0;
			button->timeFromClickToClick = 0;
			button->state = STATE_DOUBLE;
			printClick(button->state);
			MainTimer_unregisterCallbck(onButtonPeriodicEvent, button);
		}
		if((button->timeFromClickToClick) >200)
		{
			button->timeFromClickToClick = 0;
			button->click = 0;
			button->state = STATE_SHORT;
			printClick(button->state);
			MainTimer_unregisterCallbck(onButtonPeriodicEvent, button);
		}
	}
}
