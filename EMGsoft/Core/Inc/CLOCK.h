/*
 * CLOCK.H
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#pragma once
#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_


typedef struct TimeClock_
{
	TIM_HandleTypeDef * timer;
	int counter;
	uint32_t  load;
} Clock;

void clockInit(Clock * TIM, TIM_HandleTypeDef * timer , uint32_t  autoreload );

void getTime(Clock * TIM);

void onClockPeriodicEvent();
#endif /* INC_CLOCK_H_ */
