/*
 * FLASH.h
 *
 *  Created on: 6 Sep 2022
 *      Author: student
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_
#include "main.h"
typedef enum FlashState
{
	WRITE,
	DELAET,
	PENDING,
	READY,
}state;

typedef struct useFlesh
{
	char text[128];
	FLASH_EraseInitTypeDef myflesh;
	int sizeOfData;
	uint32_t placeInflesh;
	uint64_t textToInt;
	state statenow;


}useFlesh;

void writeToFlesh(useFlesh * data);

void eraseFromFlash(useFlesh * data , uint32_t page );

void FleshinitData(useFlesh * data , char * info);

#endif /* INC_FLASH_H_ */
