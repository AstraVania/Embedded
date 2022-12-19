/*
 * Flesh.h
 *
 *  Created on: 23 Oct 2022
 *      Author: student
 */

#ifndef INC_FLESH_H_
#define INC_FLESH_H_
#include "main.h"
//typedef enum FlashState
//{
//	WRITE,
//	DELAET,
//	PENDING,
//	READY,
//}state;

typedef struct useFlesh
{
	char text[256];
	FLASH_EraseInitTypeDef myflesh;
	int sizeOfData;
	uint32_t placeInflesh;
}useFlesh;


void writeToFlesh(useFlesh * data);


void FleshinitData(useFlesh * data , char * info, uint32_t infoSize);


void eraseFromFlash(useFlesh * data , uint32_t page );
#endif /* INC_FLESH_H_ */
