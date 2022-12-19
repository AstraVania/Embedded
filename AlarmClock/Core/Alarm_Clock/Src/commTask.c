/*
 * commTask.c
 *
 *  Created on: Oct 20, 2022
 *      Author: student
 */
#include "main.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "commTask.h"

extern UART_HandleTypeDef huart2;
static int _cmdCount = 0;
static uint8_t _buffer[1000];
#define NUMBER_OF_COMMANDS 10
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
		if (_cmdCount >= 100)
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

	char info[100];
	char cmd[100];
	int commandPlace = 0;
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
