
#pragma once
#ifndef INC_COMMTASK_H_
#define INC_COMMTASK_H_

typedef void (*HandlerFunc)(void* obj, char * param);

typedef struct command
{
	HandlerFunc function;
	char * name;
	void * funcobj;
}COMMAND;

int commTask();

void handleCommand();

#define RING_BUFFER_SIZE 100

void RegisterCommand(char* fname ,HandlerFunc Func , void * obj);


#endif /* INC_COMMTASK_H_ */
