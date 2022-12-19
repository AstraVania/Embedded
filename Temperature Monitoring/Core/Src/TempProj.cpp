/*
 * mymain.cpp
 *
 *  Created on: Nov 15, 2022
 *      Author: student
 */
#include "main.h"
#include <stdarg.h>
#include "CommTask.h"
#include "cmsis_os2.h"

#include "fatfs.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "LED.h"
#include "MainTimer.h"
#include "DHT.h"
#include "buzzer.h"
#include "Rtc.h"
#include "Filehandler.h"
#include "cppCli.h"
#include "Flash.h"

#define MAGIC 0xABC
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern I2C_HandleTypeDef hi2c1;

threshold _threshold(30, 40); //Default
LED RedLed(LD1_GPIO_Port, LD1_Pin);
MainTimer *Timer = nullptr;
DHT *_dht;
buzzer *_buzzer;
Rtc *_rtc;
cppCli *cli;
Filehandler *_logfile;
Filehandler *_logcrit;
Flash *_tempflesh;

char buffer[100];



extern "C" void TempProj() {
	_tempflesh = new Flash();
	_logcrit = new Filehandler("crit.txt");
	_logfile = new Filehandler("test.txt");
	_rtc = new Rtc(&hi2c1, 0xD0);
	_buzzer = new buzzer(&htim3, TIM_CHANNEL_1);
	_dht = new DHT(TEMP_GPIO_Port, TEMP_Pin, &htim7);
	Timer = new MainTimer(&htim6, 10);
	Timer->MainTimer_Start();
	cli->cliInit();
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	uint32_t *read = (uint32_t*) (0x08080000);
	if (MAGIC == *read) {
		read++;
		_threshold.setcrit(*read);
		read++;
		_threshold.setwarning(*read);
	}

}

extern "C" void SaveLog(void *argument) {
	DateTime getDate;


	for (;;) {

		_rtc->rtcGetTime(&getDate);
		sprintf(buffer,
				"The Date is %02d/%02d/%02d The Time is %02d:%02d:%02d The Temperature %.2f %s\n\r",
				getDate.day, getDate.month, getDate.year, getDate.hours,
				getDate.min, getDate.sec, _dht->Dht_getTempperature(), _threshold.getmassage(_dht->Dht_getTempperature()));
		_logfile->writeToFile(buffer);
		osDelay(60 * 1000);
	}
}

extern "C" void cmd(void *argument) {

	for (;;) {
		if (commTask()) {
			handleCommand();
		}
		osDelay(1);
	}
}

extern "C" void redWarnning(void *argument)
{
	int flagOnce = 0;
	SystemState State;
	double temperature;
	for (;;)
	{
		temperature = _dht->Dht_getTempperature();
		_threshold.setState(temperature);
		State = _threshold.getState();

	    if (State == CRITICAL)
	    {
	    	if(flagOnce!=1)
	    	{
				_buzzer->buzStart();
				RedLed.setstate(BLINK);
				flagOnce = 1;
	    	}
		}
	    else if (State == WARNING)
		{
	    	if(flagOnce!=2)
	        {
				RedLed.on();
				RedLed.setstate(ON);
				flagOnce=2;
	        }
		}
	    else
	    {
	    	flagOnce = 0;
	    }
		if(State != NORMAL)
		{
			_logcrit->writeToFile(buffer);
		}

		if (RedLed.getstate() == BLINK)
		{
			RedLed.toggle();
		}
		_dht->Dht_readAsync();
		osDelay(1000);
	}
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == RB_Pin) {
		_buzzer->buzOff();
		RedLed.off();
	}
	if (GPIO_Pin == TEMP_Pin) {
		_dht->Dht_onGpioInterrupt(TEMP_Pin);

	}
}

extern "C" void PeriodElapsedCallback() {
	if (Timer) {
		Timer->onInterrupt();
	}
}
