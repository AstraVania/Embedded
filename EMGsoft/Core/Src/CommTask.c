/*
 * CommTask.c
 *
 *  Created on: Jul 10, 2022
 *      Author: Oren Barzam
 */
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <CommTask.h>
#include <main.h>

#define NUMBER_OF_COMMANDS 10
extern UART_HandleTypeDef huart2;
static int _cmdCount = 0;
static uint8_t _buffer[RING_BUFFER_SIZE];
int _commandPlaceInArr = 0;
COMMAND _commandArr[NUMBER_OF_COMMANDS];

void RegisterCommand(char* commandName ,HandlerFunc func , void * obj)
{

	_commandArr[_commandPlaceInArr].name = commandName;
	_commandArr[_commandPlaceInArr].function =  func;
	_commandArr[_commandPlaceInArr].funcobj = obj;
	_commandPlaceInArr++;
}

int commTask()
{
	uint8_t ch;
	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 0);//get char
	if (Status != HAL_OK)
	{
		return 0;
	}
	if (ch != '\r' && ch != '\n')
	{
		HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);//echo
		if (_cmdCount >= RING_BUFFER_SIZE)
		{
			_cmdCount = 0;
		}
		_buffer[_cmdCount++] = ch;
		return 0;
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);
	_buffer[_cmdCount] = 0;
	_cmdCount = 0;
	return 1;
}

void handleCommand()
{
	char info[20];///for next step
	int commandPlace = 0;
	char cmd[20];
	int params = sscanf((const char*)_buffer, "%s %s", cmd , info);
	if (params == 0)
	{
		  return;
	}
	while(_commandArr[commandPlace].name != NULL)
	{
		if((strcmp(_commandArr[commandPlace].name , cmd))==0)
		{
			_commandArr[commandPlace].function(_commandArr[commandPlace].funcobj , info);
			return;
		}
		commandPlace++;
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)"NO SUCH COMMAND\n\r", 17, 0xFFFF);
}

