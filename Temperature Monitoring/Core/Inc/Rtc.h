/*
 * Rtc.h
 *
 *  Created on: 20 Nov 2022
 *      Author: student
 */
#include "main.h"
#ifndef INC_RTC_H_
#define INC_RTC_H_

typedef struct DateTime_
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
} DateTime;

class Rtc {
private:
	I2C_HandleTypeDef * _hi2c;
    uint8_t _devAddr;
    DateTime * _dateTime;

public:
    Rtc(I2C_HandleTypeDef * hi2c, uint8_t devAddr ):
    	_hi2c(hi2c) , 	_devAddr(devAddr){}


    void rtcGetTime(DateTime * dateTime);

    void rtcSetTime(DateTime * dateTime);

    void setDate(char * param);

	~Rtc(){}
};

#endif /* INC_RTC_H_ */







