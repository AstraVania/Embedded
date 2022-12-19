/*
 * Flash.h
 *
 *  Created on: Nov 29, 2022
 *      Author: student
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_
#include "stdint.h"
#include "main.h"
#include <string.h>

typedef struct Data
{
   uint32_t MagicNumber;
   uint32_t startCrit;
   uint32_t startWarninng;
}startup;



class Flash
{
private:


	FLASH_EraseInitTypeDef myflesh;
	uint64_t sizeOfData = sizeof(startup);
	uint32_t placeInflesh = (256)*2048 + 0x08000000;
public:
	Flash()
	{

		myflesh.NbPages = 1;
		myflesh.Page = 256;
		myflesh.Banks = FLASH_BANK_2;
		myflesh.TypeErase = FLASH_TYPEERASE_PAGES;
	}
	void eraseFromFlash();
	void writeToFlesh(uint32_t crit , uint32_t warning);
	virtual ~Flash();
};

#endif /* INC_FLASH_H_ */


//void FleshinitData(useFlesh * data , char * info)
//{
//	strcpy(data->text, info);
//	data->sizeOfData =  strlen(data->text) / 8 + 1;
//	data->textToInt =  *(uint64_t*)(data->text);
//	data->statenow = PENDING;
//}






