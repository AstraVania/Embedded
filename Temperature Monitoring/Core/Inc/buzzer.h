/*
 * buzzer.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "stdint.h"
#include "main.h"
#include "TimerTask.h"
typedef enum BuzzerState_
{
	BUZ_STATE_OFF,
	BUZ_STATE_ON,
} BuzzerState;


class buzzer: public TimerTask
{

private:
	TIM_HandleTypeDef* _pwmTimer;
	uint32_t _channel;
	BuzzerState _state = BUZ_STATE_OFF;
	int _noteIdx = 0;
	int _notesCount;
	uint32_t  _noteLengths = 0;
public:
	buzzer(TIM_HandleTypeDef* pwmTimer, uint32_t channel ):
		_pwmTimer(pwmTimer) , 	_channel(channel){}

	void buzOff();
	void buzStart();
	void timerFunc();
	~buzzer(){}
};

#endif /* INC_BUZZER_H_ */





//#endif
