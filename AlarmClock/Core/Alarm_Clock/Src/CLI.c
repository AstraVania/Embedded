/*
 * CLI.c
 *
 *  Created on: 23 Oct 2022
 *      Author: student
 */




#include <CLI.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "main.h"
//#include "DHT.h"
#include "CommTask.h"
//#include "BUTTON.h"
//#include "CLOCK.h"
#include "LED.h"
#include "BUZZER.h"
#include "Commtask.h"
#include "Rtc.h"
#include "Alarm.h"
extern Rtc _rtc;
extern Led _redLed;
//extern Dht _dhtt;
extern Buzzer _buzzer;
//extern Clock _secClock;
DateTime getTime;

void ledOnCmd(void * obj, char * param)
{
	Led * led = (Led *)obj;
	ledOn(led);
}

void ledOffCmd(void * obj, char * param)
{
	Led * led = (Led *)obj;
	ledOff(led);
}

void ledBlinkCmd(void * obj, char * param)
{
	Led * led = (Led *)obj;
	ledBlink(led);
}
void printAlarmCmd(void * obj, char * param)
{
	printAlarms();
}
void delAlarmCmd(void * obj, char * param)
{
	int alarm_num;
	sscanf((const char*)param, "%d" , &alarm_num);
	deleteAlarm(alarm_num);

}
void addAlarmCmd(void * obj, char * param)
{
	Rtc * rtc = (Rtc *)obj;
	rtcGetTime(rtc,&getTime);
	int params = sscanf((const char*)param, "%d:%d", &getTime.hours , &getTime.min);
	if(params!=2 || getTime.hours>24 ||getTime.hours<0 || getTime.min < 0 || getTime.min > 59)
	{
		printf("wrong alarm add format\n\r");
		return;

	}
	else
	{
		addAlarm(getTime);
	}


}
void setDateCmd(void * obj, char * param)
{
	DateTime timeNow;
	int params = sscanf((const char*)param, "%d/%d/%d/%d", &timeNow.day , &timeNow.month ,&timeNow.year ,&timeNow.weekDay);
	if(params!=4 || timeNow.day>31 || timeNow.day<1 || timeNow.month < 1 || timeNow.month > 12 || timeNow.year < 22 || timeNow.year > 99 ||  timeNow.weekDay > 6 ||timeNow.weekDay < 0)
	{
			printf("Date was not set ,wrong parameters\n\r");
			return;
	}
	else
	{
			printf("Date was set successfully\n\r");
	}
	    Rtc * rtc = (Rtc *)obj;
		rtcGetTime(rtc,&getTime);
		timeNow.hours = getTime.hours;
		timeNow.min = getTime.min;
		timeNow.sec = getTime.sec;
		rtcSetTime(rtc,&timeNow);

}
void getDateCmd(void * obj, char * param)
{
	Rtc * rtc = (Rtc *)obj;
	rtcGetTime(rtc,&getTime);
	printf("The Date Now %02d/%02d/%02d \r\n" ,getTime.day ,getTime.month ,getTime.year);
	printf("The Day Today is %s\r\n" ,weekdays[getTime.weekDay+1]);

}
void getTimeCmd(void * obj, char * param)
{
	Rtc * rtc = (Rtc *)obj;
	rtcGetTime(rtc,&getTime);
	printf("The Time Now %02d:%02d:%02d \r\n" ,getTime.hours ,getTime.min ,getTime.sec);
}
void setTimeCmd(void * obj, char * param)
{
	DateTime timeNow;
	int params = sscanf((const char*)param, "%d:%d:%d", &timeNow.hours , &timeNow.min ,&timeNow.sec);
	if(params!=3 || timeNow.hours>24 || timeNow.hours<0 || timeNow.min < 0 || timeNow.min > 59 || timeNow.sec < 0 || timeNow.sec > 59 )
	{
		printf("Time was not set ,wrong parameters\n\r");
		return;
	}
	else
	{
		printf("Time was set successfully\n\r");
	}
	Rtc * rtc = (Rtc *)obj;
	rtcGetTime(rtc,&getTime);
	timeNow.day = getTime.day;
	timeNow.month = getTime.month;
	timeNow.year = getTime.year;
	timeNow.weekDay = getTime.weekDay;
	rtcSetTime(rtc,&timeNow);
}
void stopAlarmCmd(void * obj, char * param)
{
	Buzzer * buz = (Buzzer *)obj;
	buzOff(buz);
}
void cliInit()
{
	RegisterCommand("del.alarm", delAlarmCmd , &_rtc);
	RegisterCommand("set.date", setDateCmd , &_rtc);
	RegisterCommand("get.date", getDateCmd , &_rtc);
	RegisterCommand("set.time", setTimeCmd , &_rtc);
	RegisterCommand("get.time", getTimeCmd , &_rtc);
	RegisterCommand("add.alarm", addAlarmCmd , &_rtc);
	RegisterCommand("add.alarm", addAlarmCmd , &_rtc);
	RegisterCommand("pri.alarm", printAlarmCmd , &_rtc);
	RegisterCommand("stop", stopAlarmCmd , &_buzzer);
//	RegisterCommand("led.on", ledOnCmd , &_redLed);
//	RegisterCommand("led.off", ledOffCmd , &_redLed);
//	RegisterCommand("led.blink", ledBlinkCmd , &_redLed);
//	RegisterCommand("buzz.on", buzzOnCmd , &_buzzer);
//	RegisterCommand("buzz.off", buzzOffCmd , &_buzzer);
//	RegisterCommand("get.time", timeCmd , &_secClock);
//	RegisterCommand("get.temp",dhtCmd ,&_dhtt);
}



