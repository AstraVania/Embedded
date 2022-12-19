/*
 * LED1.cpp
 *
 *  Created on: 6 Nov 2022
 *      Author: student
 */

#include <LED.h>
#include <main.h>


LED::~LED()
{
	// TODO Auto-generated destructor stub
}

void LED::toggle()
{

	HAL_GPIO_TogglePin(_port ,_pin);
}
void LED::off()
{
	//Timer->MainTimer_unregisterCallbck(this);
	_state = OFF;
	_maxPeriod = 0;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}
void LED::on()
{
	_maxPeriod = 0;
	HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}


void LED::setstate(lstate newstate)
{
	_state = newstate;
}
int LED:: getstate()
{
	return _state;
}
void LED::timerFunc()
{
        _timeCounter++;
	if (_timeCounter >= _maxPeriod && _maxPeriod > 0)
	{
		_timeCounter = 0;
		toggle();
	}
}
