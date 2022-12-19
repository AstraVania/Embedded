
#include "Dht.h"
#include "MainTimer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BITS 40

enum DhtState
{
	DHT_STATE_NO_DATA,
	DHT_STATE_READY,
	DHT_STATE_ERROR,
	DHT_STATE_POWER_ON,
	DHT_STATE_POWER_ON_ACK,
	DHT_STATE_INIT_RESPONSE,
	DHT_STATE_RECEIVE_DATA
};

void Dht_init(Dht * dht, GPIO_TypeDef * gpioPort, uint16_t gpioPin, TIM_HandleTypeDef * timer)
{
	dht->gpioPort = gpioPort;
	dht->gpioPin = gpioPin;
	dht->timer = timer;
	dht->counter = 0;
	dht->maxCounter = 0;
	dht->state = DHT_STATE_NO_DATA;
	dht->temperature = 0.0;
	dht->humidity = 0.0;
}

static void setGpioOutput(Dht * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = dht->gpioPin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht->gpioPort, &gpioStruct);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

static void setGpioExti(Dht * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = dht->gpioPin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(dht->gpioPort, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void Dht_onTimerInterrupt(void * obj)
{
	Dht * dht = (Dht *)obj;
	if (dht->state != DHT_STATE_POWER_ON) {
		return;
	}
	dht->counter++;
	if (dht->counter >= dht->maxCounter)
	{
		dht->state = DHT_STATE_POWER_ON_ACK;
		HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 1);
		HAL_TIM_Base_Start(dht->timer);
		__HAL_TIM_SET_COUNTER(dht->timer, 0);
		setGpioExti(dht);
		dht->counter = 0;
		MainTimer_unregisterCallbck(Dht_onTimerInterrupt, dht);
	}
}

void Dht_readAsync(Dht * dht)
{
	setGpioOutput(dht);
	HAL_GPIO_WritePin(dht->gpioPort, dht->gpioPin, 0);
	MainTimer_registerCallbck(Dht_onTimerInterrupt, dht);
	dht->counter = 0;
	dht->maxCounter = 19;
	dht->state = DHT_STATE_POWER_ON;
}

void Dht_onGpioInterrupt(Dht * dht, uint16_t pin)
{
	if (dht->gpioPin != pin)
	{
		return;
	}
	uint32_t timeMs = __HAL_TIM_GET_COUNTER(dht->timer);
	switch (dht->state)
	{
	case DHT_STATE_POWER_ON_ACK:
		if (timeMs > 50)
		{
			dht->state = DHT_STATE_ERROR;
		}
		dht->state = DHT_STATE_INIT_RESPONSE;
		break;

	case DHT_STATE_INIT_RESPONSE:
		if (timeMs > 200)
		{
			dht->state = DHT_STATE_ERROR;
		}
		memset(dht->data, 0, sizeof(dht->data));
		dht->bit = 0;
		dht->state = DHT_STATE_RECEIVE_DATA;
		break;

	case DHT_STATE_RECEIVE_DATA:
		{
			if (timeMs > 140)
			{
				dht->state = DHT_STATE_ERROR;
			}

			int byte = dht->bit / 8;
			dht->data[byte] <<= 1;

			if (timeMs > 100)
			{
				dht->data[byte] |= 1;
			}

			dht->bit++;
			if (dht->bit >= MAX_BITS)
			{
				uint8_t checksum = dht->data[0] + dht->data[1] +
						dht->data[2] + dht->data[3];

				if (checksum == dht->data[4])
				{
					dht->state = DHT_STATE_READY;
					dht->humidity = (double)dht->data[0] + ((double)dht->data[1]) / 10;
					dht->temperature = (double)dht->data[2] + ((double)dht->data[3]) / 10;
					Dht_print(dht);
				}
				else
				{
					dht->state = DHT_STATE_ERROR;
				}

				// stop timer and disable GPIO interrupts
				HAL_TIM_Base_Stop(dht->timer);
				HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
			}

		}
		break;

	default:

		break;
	}

	__HAL_TIM_SET_COUNTER(dht->timer, 0);
}

int Dht_hasData(Dht * dht)
{
	int hasData = dht->state == DHT_STATE_READY;

	if (hasData)
	{
		dht->state = DHT_STATE_NO_DATA;
	}
	return hasData;
}

double Dht_getHumidty(Dht * dht)
{
	return dht->humidity;
}

double Dht_getTempperature(Dht * dht)
{
	return dht->temperature;
}

void Dht_print(Dht * dht)
{
   printf("The temperature is : %.2f The humidity is : %.2f\n\r" ,dht->temperature,dht->humidity );
}
