/*
 * MainTimer.h
 *
 *  Created on: Nov 8, 2022
 *      Author: student
 */
#pragma once
//#include "TimerTask.h"
#include "stdint.h"
#include "main.h"
#ifndef INC_MAINTIMER_H_
#define INC_MAINTIMER_H_



class TimerTask;


class MainTimer {
private:
	TIM_HandleTypeDef * timer;
	uint32_t  autoreload;
	uint8_t numberOftimers = 0;
	TimerTask * _timeArr[10];
public:
	MainTimer(TIM_HandleTypeDef * _timer , uint32_t _autoreload) :
		timer(_timer), autoreload(_autoreload), numberOftimers(0)
	{
		  __HAL_TIM_SET_AUTORELOAD(_timer, autoreload);
		 // HAL_TIM_Base_Start_IT(_timer);
	}

	virtual ~MainTimer();
	bool isMyTimer(TIM_HandleTypeDef * t) const { return timer == t; }
    void MainTimer_Start();
	void MainTimer_registerCallbck(TimerTask * time);
	void MainTimer_unregisterCallbck(TimerTask * time);
	void onInterrupt();
};




#endif /* INC_MAINTIMER_H_ */



