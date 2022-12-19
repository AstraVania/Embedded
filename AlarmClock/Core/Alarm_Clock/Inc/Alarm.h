/*
 * Alarm.h
 *
 *  Created on: 23 Oct 2022
 *      Author: student
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_




typedef struct Alarm_
{
	uint32_t Alarmtime;
	int AlarmNum;
	int alarm_hours;
	int alarm_min;
} Alarm;

void printAlarms();

void initAlarms();

void deleteAlarm(int thisAlarm);

void checkAlarms(uint32_t seconds);

void addAlarm(DateTime AlarmTime);
#endif /* INC_ALARM_H_ */
