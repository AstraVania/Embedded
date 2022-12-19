/*
 * FLASH.c
 *
 *  Created on: 6 Sep 2022
 *      Author: student
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "FLASH.h"

extern useFlesh _flesh;

void FleshinitData(useFlesh * data , char * info)
{
	strcpy(data->text, info);
	data->sizeOfData =  strlen(data->text) / 8 + 1;
	data->textToInt =  *(uint64_t*)(data->text);
	data->statenow = PENDING;
}


void writeToFlesh(useFlesh * data)
{
	static uint64_t next = 0;
	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, data->placeInflesh + next, *(uint64_t*)(data->text + next));
	next+=8;
	if((data->sizeOfData * 8)+1 < next)
	{
		data->statenow = READY;
		next = 0;
		data->placeInflesh +=next;
	}

}

void eraseFromFlash(useFlesh * data , uint32_t page )
{
	data->myflesh.NbPages = 1;
	data->myflesh.Page = page;
	if(data->myflesh.Page >= 256)
	{
		data->myflesh.Banks = FLASH_BANK_2;
	}
	else
	{
		data->myflesh.Banks = FLASH_BANK_1;
	}
	data->myflesh.TypeErase = FLASH_TYPEERASE_PAGES;
	data->placeInflesh =  page*2048 + 0x08000000;
	HAL_FLASHEx_Erase_IT(&data->myflesh);
	data->statenow = PENDING;

}

void MyFlashinterruptHandler()
{
   if(_flesh.statenow == PENDING || _flesh.statenow == READY)
   {
	   return;
   }
   if(_flesh.statenow == WRITE)
   {
	   writeToFlesh(&_flesh);
	   return;
   }
   if(_flesh.statenow == DELAET)
   {
	   //delatFromFlesh(&data);
	   return;
   }

}

void printFlash()
{
    if(_flesh.statenow == READY)
    {
    	char * read = (char *)(0x08080000);
    	printf("the data is %s \n\r" ,read);
    	HAL_FLASH_Lock();
    	_flesh.statenow = PENDING;
    }

}

void  findFreeFlesh(useFlesh * data)
{
	uint32_t * find = (uint32_t *)(0x08080000);
	int i = 0;
	while(find[i] != 0xFFFFFFFF)
	{
		i++;
	}
	data->placeInflesh = (uint32_t)&(find[i]);
}

//char * info = "gagaghaqhHRJNRJRJRKM" ;
//FleshinitData(&data , info);
//delatFromFlesh(&data, 256);
