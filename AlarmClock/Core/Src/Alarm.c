/*
 * Alarmc.c
 *
 *  Created on: 23 Oct 2022
 *      Author: student
 */




#include <stdio.h>
#include "Rtc.h"
#include "Alarm.h"
#include "Flesh.h"
#include "BUZZER.h"
extern Buzzer _buzzer;
extern useFlesh _data;
Alarm AlarmOn[10];

void initAlarms()
{
	for(int i = 0 ; i <10 ; i++)
	{
		Alarm * temp = (Alarm *)(0x08080000 + (i*sizeof(AlarmOn[0])));
		AlarmOn[i] = temp[i];
	}
}
void addAlarm(DateTime AlarmTime)
{

  Alarm	newAlarm;
  for(int freeAlarm = 0 ; freeAlarm < 10 ; freeAlarm++ )
  {
	  if(AlarmOn[freeAlarm].AlarmNum == -1)
	  {
		  newAlarm.Alarmtime = timeGetSeconds(AlarmTime);
		  newAlarm.alarm_hours = AlarmTime.hours;
		  newAlarm.alarm_min = AlarmTime.min;
		  AlarmOn[freeAlarm] = newAlarm;
		  AlarmOn[freeAlarm].AlarmNum = freeAlarm;
		  char * info = (char *)(&AlarmOn);
		  eraseFromFlash(&_data, 256);
		  FleshinitData(&_data , info, sizeof(AlarmOn));
		  writeToFlesh(&_data);
		  printf("Alarm added successfully\n\r");
		  return;
	  }
  }
  printf("Failed to add new Alarm \n\r");
}

void deleteAlarm(int thisAlarm)
{
	if(AlarmOn[thisAlarm].AlarmNum == -1)
	{
		return;
	}
	if(thisAlarm>10 || thisAlarm<-1 )
	{
		 printf("Failed to delete new Alarm \n\r");
		 return;
	}
	AlarmOn[thisAlarm].AlarmNum = -1;
	char * info = (char *)(&AlarmOn);
	eraseFromFlash(&_data, 256);
    FleshinitData(&_data , info, sizeof(AlarmOn));
    writeToFlesh(&_data);
    printf("Alarm deleted successfully\n\r");

}

void checkAlarms(uint32_t seconds)
{
	int i = 0;
	for(i = 0 ; i < 10 ; i++)
	{
	   if(AlarmOn[i].Alarmtime == seconds )
	   {
		   printf("alarm On %d\n\r" ,AlarmOn[i].AlarmNum);
		   music(&_buzzer);
		   deleteAlarm(AlarmOn[i].AlarmNum);
		   break;
	   }
	}
}

void printAlarms()
{
	for(int i = 0 ; i<10 ; i++)
	{
		if(AlarmOn[i].AlarmNum != -1)
		{
			printf("Alarm on in  %02d:%02d  and alarm number is %d\n\r" ,AlarmOn[i].alarm_hours ,AlarmOn[i].alarm_min,AlarmOn[i].AlarmNum);
		}
	}
}







