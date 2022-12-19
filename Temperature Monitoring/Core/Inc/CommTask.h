
#pragma once
#ifndef INC_COMMTASK_H_
#define INC_COMMTASK_H_
#include "cppCli.h"
typedef void (*HandlerFunc)(void* obj, char * param);

typedef struct command
{
	char name[10];
	cppCli * command;
}COMMAND;

int commTask();

void handleCommand();

#define RING_BUFFER_SIZE 100

void RegisterCommand(const char* commandName , cppCli * commad);


#endif /* INC_COMMTASK_H_ */
