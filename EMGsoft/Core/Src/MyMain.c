
#include "MyMain.h"
#include "main.h"
#include "BUTTON.h"
#include "CLOCK.h"
#include "LED.h"
#include "RingBuffer.h"
#include "BUZZER.h"
#include "CommTask.h"
#include "CLI.h"
#include "DHT.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FLASH.h"

extern UART_HandleTypeDef huart2;
extern ButtonState _stateNow;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

Led _redLed;
Led _blueLed;
Button _rightButton;
Button _leftButton;
uint32_t _lightSensorValue;
Dht _dhtt;
Buzzer _buzzer;
Clock _secClock;
useFlesh _flesh;
#define ADC 410


int _write(int fd, char* ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}

void mainloop()
{
	ledInit(&_redLed , RLED_GPIO_Port, RLED_Pin);
	buttonInit(&_rightButton , RB_GPIO_Port , RB_Pin);
	buttonInit(&_leftButton , LB_GPIO_Port , LB_Pin);
	clockInit(&_secClock, &htim6, 10 );
	buzzerInit(&_buzzer , &htim3, TIM_CHANNEL_1);
	Dht_init(&_dhtt , TEMP_GPIO_Port , TEMP_Pin , &htim7);
	HAL_TIM_Base_Start(&htim7);
	HAL_TIM_Base_Start(&htim2);//PWM FOR LED
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_ADC_Start_IT(&hadc1);
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	cliInit();
//	delatFromFlesh( &_flesh , 256 );
while(1)
{
//	int tt; //DHT TO FLESH
//	char tempbuf [100];
//    if(HAL_GetTick()%1000 == 0)
//    {
//    	tt++;
//    	Dht_readAsync(&_dhtt);
//    	if(_dhtt.state == 1)
//    	{
//    	   snprintf( tempbuf, 100, "The temperature is : %.2f The humidity is : %.2f in time %d\n\r" ,_dhtt.temperature,_dhtt.humidity,tt);
//    	   FleshinitData(&_flesh , tempbuf);
//    	   writeToFlesh(&_flesh);
//
//    	}
//    }


	ledControlBrightness(&htim2 ,TIM_CHANNEL_1, _lightSensorValue/ADC);

    if(commTask())
	{
    	handleCommand();
	}
	ButtonState buttonState = getButtonState(&_rightButton); ///button control
	switch (buttonState)
	{
		case Undefined    :
			break;
		case STATE_SHORT :
			ledOn(&_redLed);
			buzStart(&_buzzer);
			printf("LED ON\n\r");
			resetButtonState(&_rightButton);
			break;
		case STATE_LONG :
			ledOff(&_redLed);
			buzOff(&_buzzer);
			printf("LED OFF\n\r");
			resetButtonState(&_rightButton);
			break;
		case STATE_DOUBLE :
			ledBlink(&_redLed);
			printf("BLINK\n\r");
			resetButtonState(&_rightButton);
			break;
		default :
			break;
	 }

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	static uint32_t _pressTime;
	static uint32_t _releaseTime;
	if(GPIO_Pin == RB_Pin)
	{
		if(HAL_GPIO_ReadPin(_rightButton. GPIOx, _rightButton.GPIO_Pin)==0)
		{
			_pressTime  = HAL_GetTick();
		}
        if(HAL_GPIO_ReadPin(_rightButton. GPIOx, _rightButton.GPIO_Pin)==1)
        {
        	_releaseTime = HAL_GetTick();
        	presseState(&_rightButton ,_releaseTime - _pressTime );
        }
	}
	if(GPIO_Pin == TEMP_Pin )
	{
		Dht_onGpioInterrupt(&_dhtt, TEMP_Pin);
	}

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

	 _lightSensorValue = HAL_ADC_GetValue(&hadc1);
}
