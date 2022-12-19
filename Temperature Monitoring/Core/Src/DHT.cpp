/*
 * DHT.cpp
 *
 *  Created on: Nov 15, 2022
 *      Author: student
 */

#include "DHT.h"
#include "main.h"
#include <cstring>
#include <iostream>
#include <string.h>
#include "DHT.h"
#include "MainTimer.h"

#include <sstream>
#define MAX_BITS 40
extern MainTimer * Timer;



void DHT::setGpioOutput()
{
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

void DHT::setGpioExti()
{
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = _gpioPin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(_gpioPort, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void DHT::timerFunc()
{
	if (_state != DHT_STATE_POWER_ON) {
		return;
	}
	_counter++;
	if (_counter >= _maxCounter)
	{
		_state= DHT_STATE_POWER_ON_ACK;
		HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
		HAL_TIM_Base_Start(_timer);
		__HAL_TIM_SET_COUNTER(_timer, 0);
		setGpioExti();
		_counter = 0;
		Timer->MainTimer_unregisterCallbck(this);
	}
}

void DHT::Dht_readAsync()
{
	setGpioOutput();
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
	Timer->MainTimer_registerCallbck(this);
	_counter = 0;
	_maxCounter = 19;
	_state = DHT_STATE_POWER_ON;
}

void DHT::Dht_onGpioInterrupt(uint16_t pin)
{
	if (_gpioPin != pin)
	{
		return;
	}
	uint32_t timeMs = __HAL_TIM_GET_COUNTER(_timer);
	switch (_state)
	{
	case DHT_STATE_POWER_ON_ACK:
		if (timeMs > 50)
		{
			_state = DHT_STATE_ERROR;
		}
		_state = DHT_STATE_INIT_RESPONSE;
		break;

	case DHT_STATE_INIT_RESPONSE:
		if (timeMs > 200)
		{
			_state = DHT_STATE_ERROR;
		}
		memset(_data, 0, sizeof(_data));
		_bit = 0;
		_state = DHT_STATE_RECEIVE_DATA;
		break;

	case DHT_STATE_RECEIVE_DATA:
		{
			if (timeMs > 140)
			{
				printf("ERROR: time %lu\n\r " , timeMs);
				_state = DHT_STATE_ERROR;
			}

			int byte = _bit / 8;
			_data[byte] <<= 1;

			if (timeMs > 100)
			{
				_data[byte] |= 1;
			}

			_bit++;
			if (_bit >= MAX_BITS)
			{
				uint8_t checksum = _data[0] + _data[1] +
						_data[2] + _data[3];

				if (checksum == _data[4])
				{
					_state = DHT_STATE_READY;
					_humidity = (double)_data[0] + ((double)_data[1]) / 10;
					_temperature = (double)_data[2] + ((double)_data[3]) / 10;

				}
				else
				{
					_state = DHT_STATE_ERROR;
				}

				HAL_TIM_Base_Stop(_timer);
				HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
			}

		}
		break;

	default:

		break;
	}

	__HAL_TIM_SET_COUNTER(_timer, 0);
}

int DHT::Dht_hasData()
{
	if(_state == DHT_STATE_READY)
		return 1;
	else
		return 0;

}


double DHT::Dht_getTempperature()
{
	return _temperature;
}

