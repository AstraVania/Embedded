/*
 * DHT.h
 *
 *  Created on: Nov 15, 2022
 *      Author: student
 */
#include "main.h"
#include "TimerTask.h"
#ifndef INC_DHT_H_
#define INC_DHT_H_

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

class DHT : public TimerTask
{
private:
	GPIO_TypeDef * _gpioPort;
	uint16_t _gpioPin;
	TIM_HandleTypeDef * _timer;
	int _counter = 0;
	int _maxCounter = 0;
	DhtState _state = DHT_STATE_NO_DATA;
	uint8_t _data[5];
	int _bit;
	double _temperature = 0.0;
	double _humidity = 0.0;

public:
	DHT(GPIO_TypeDef * gpioPort, uint16_t gpioPin , TIM_HandleTypeDef * timer):
	_gpioPort(gpioPort) , 	_gpioPin(gpioPin) , _timer(timer){}


	 ~DHT() {}
	 void Dht_readAsync();
	 void Dht_onGpioInterrupt(uint16_t pin);
	 void setGpioOutput();
	 void setGpioExti();
	 int Dht_hasData();
	 double Dht_getHumidty();
	 double Dht_getTempperature();
	 void timerFunc();
	 void Dht_print(); //delate
};

#endif /* INC_DHT_H_ */




