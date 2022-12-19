/*
 * LED1.h
 *
 *  Created on: 6 Nov 2022
 *      Author: student
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include "main.h"

//#include "TimerTask.h"
typedef enum LED_STATE
{
	ON,
	OFF,
	BLINK,
}lstate;


class LED //: public TimerTask
{
private:

	GPIO_TypeDef * _port;
    uint16_t _pin;
    lstate _state = OFF;
    int _timeCounter = 0;
    int _maxPeriod = 0;

public:


    LED(GPIO_TypeDef * port, uint16_t pin):
    	_port(port),
		_pin(pin)
    {
    }

    ~LED();
	void toggle();
	void off();
	void on();
	void setstate(lstate _state);
	int getstate();
	void timerFunc();
};


#endif /* INC_LED_H_ */
