

#include <string>
#include <cppCli.h>
#include "stdio.h"
#include "CommTask.h"
#include "Rtc.h"
#include "Flash.h"
#include "Filehandler.h"

extern Filehandler *_logfile;
extern Filehandler *_logcrit;
extern Rtc * _rtc;
extern threshold _threshold;
extern char buffer[100];
extern Flash _tempflesh;
extern const char* weekdays[];
cppCli::cppCli()
{
	//cliInit();
}

cppCli::~cppCli() {
	// TODO Auto-generated destructor stub
}
class setDateCmd : public cppCli
{
public:
	DateTime DateNow;

   	virtual ~setDateCmd(){}

   	void execute(char * data)
   	{
   		_rtc->rtcGetTime(&DateNow);
		int params = sscanf((const char*)data, "%d/%d/%d/%d", &DateNow.day , &DateNow.month ,&DateNow.year ,&DateNow.weekDay);
		if(params!=4 || DateNow.day>31 || DateNow.day<1 || DateNow.month < 1 || DateNow.month > 12 || DateNow.year < 22 || DateNow.year > 99 ||  DateNow.weekDay > 6 ||DateNow.weekDay < 0)
		{
				printf("Date was not set ,wrong parameters\n\r");
				return;
		}
		else
		{
				printf("Date was set successfully\n\r");
		}
		_rtc->rtcSetTime(&DateNow);
   	}


};
class getDateCmd : public cppCli
{
	DateTime getDate;
public:


   	virtual ~getDateCmd(){}
   	void execute(char * data)
   	{

   		_rtc->rtcGetTime(&getDate);
   		printf("The Date Now %02d/%02d/%02d \r\n" ,getDate.day ,getDate.month ,getDate.year);
   		printf("The Day Today is %s\r\n" ,weekdays[getDate.weekDay]);///check
   	}


};

class getTimeCmd : public cppCli
{
	DateTime getTime;
public:


   	virtual ~getTimeCmd(){}
   	void execute(char * data)
   	{


   			_rtc->rtcGetTime(&getTime);
   			printf("The Time Now %02d:%02d:%02d \r\n" ,getTime.hours ,getTime.min ,getTime.sec);
   	}


};

class setTimeCmd : public cppCli
{
	DateTime setTime;
public:


   	virtual ~setTimeCmd(){}
   	void execute(char * data)
   	{

   		    _rtc->rtcGetTime(&setTime);
   			int params = sscanf((const char*)data, "%d:%d:%d", &setTime.hours , &setTime.min ,&setTime.sec);
   			if(params!=3 || setTime.hours>24 || setTime.hours<0 || setTime.min < 0 || setTime.min > 59 || setTime.sec < 0 || setTime.sec > 59 )
   			{
   				printf("Time was not set ,wrong parameters\n\r");
   				return;
   			}
   			else
   			{
   				printf("Time was set successfully\n\r");
   			}
   		   _rtc->rtcSetTime(&setTime);
   	}


};



class setthresholdcrit : public cppCli
{
	threshold * set;
	uint8_t newParm;
public:
	setthresholdcrit(threshold *  _set) : set(_set){}
   	virtual ~setthresholdcrit(){}
   	void execute(char * data)
   	{
   		newParm = atoi(data);
        set->setcrit(newParm);
        _tempflesh.writeToFlesh(newParm ,set->getwarninng());
   	}

};

class setthresholdwarning : public cppCli
{
	threshold * set;
	uint8_t  newParm;
public:
	setthresholdwarning(threshold *  _set) : set(_set){}
   	virtual ~setthresholdwarning(){}
   	void execute(char * data)
   	{
   		newParm = atoi(data);
        set->setwarning(newParm);
        _tempflesh.writeToFlesh(set->getcrit() ,newParm);
   	}

};

class printlog : public cppCli
{

public:
	printlog(){}
   	virtual ~printlog(){}
   	void execute(char * data)
   	{
       printf("%s\n\r" , buffer);
   	}

};

class clearlog : public cppCli
{

public:
	clearlog(){}
   	virtual ~clearlog(){}
   	void execute(char * data)
   	{
   		_logcrit->clearSD();
   		_logfile->clearSD();
   	}

};
void cppCli::cliInit()
{
		RegisterCommand("set.date", new setDateCmd());
		RegisterCommand("get.date", new getDateCmd());
		RegisterCommand("set.time", new setTimeCmd());
		RegisterCommand("get.time", new getTimeCmd());
		RegisterCommand("set.crit", new setthresholdcrit(&_threshold));
		RegisterCommand("set.war",  new setthresholdwarning(&_threshold));
		RegisterCommand("log",  new printlog());
		RegisterCommand("clear",  new clearlog());

}
