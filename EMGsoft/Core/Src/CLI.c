

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "MyMain.h"
#include "main.h"
#include "DHT.h"
#include "CommTask.h"
#include "BUTTON.h"
#include "CLOCK.h"
#include "LED.h"
#include "RingBuffer.h"
#include "BUZZER.h"
#include "CLI.h"
#include "Commtask.h"

extern Led _redLed;
extern Dht _dhtt;
extern Buzzer _buzzer;
extern Clock _secClock;

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

void buzzOnCmd(void * obj, char * param)
{
	Buzzer * buzzer = (Buzzer *)obj;
	buzStart(buzzer);
}

void buzzOffCmd(void * obj, char * param)
{
	Buzzer * buzzer = (Buzzer *)obj;
	buzOff(buzzer);
}

void timeCmd(void * obj, char * param)
{
	Clock * clock = (Clock *)obj;
	getTime(clock);
}

void dhtCmd(void * obj, char * param)
{
	Dht * dht = (Dht *)obj;
	Dht_readAsync(dht);
}
void cliInit()
{
	RegisterCommand("led.on", ledOnCmd , &_redLed);
	RegisterCommand("led.off", ledOffCmd , &_redLed);
	RegisterCommand("led.blink", ledBlinkCmd , &_redLed);
	RegisterCommand("buzz.on", buzzOnCmd , &_buzzer);
	RegisterCommand("buzz.off", buzzOffCmd , &_buzzer);
	RegisterCommand("get.time", timeCmd , &_secClock);
	RegisterCommand("get.temp",dhtCmd ,&_dhtt);
}



