/*
 * Dht.h
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"

typedef struct Dht_
{
	GPIO_TypeDef * gpioPort;
	uint16_t gpioPin;
	TIM_HandleTypeDef * timer;
	int counter;
	int maxCounter;
	int state;
	uint8_t data[5];
	int bit;
	double temperature;
	double humidity;
} Dht;


void Dht_readAsync(Dht * dht);
void Dht_onTimerInterrupt(void * obj);
void Dht_onGpioInterrupt(Dht * dht, uint16_t pin);
void Dht_init(Dht * dht, GPIO_TypeDef * gpioPort, uint16_t gpioPin, TIM_HandleTypeDef * timer);
void Dht_print(Dht * dht);

#endif /* INC_DHT_H_ */
