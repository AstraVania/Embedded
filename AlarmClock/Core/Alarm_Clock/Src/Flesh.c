


#include <stdint.h>
#include "Flesh.h"
#include <stdio.h>
#include <string.h>
#include "main.h"

useFlesh _data;
void FleshinitData(useFlesh * data , char * info, uint32_t infoSize)
{
	memcpy(data->text, info, infoSize);
	data->sizeOfData =  infoSize;

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

	HAL_FLASH_Unlock();
	uint32_t error = 0;
	HAL_FLASHEx_Erase(&data->myflesh , &error);
	HAL_FLASH_Lock();
}

uint32_t  findFreeFlesh()
{
	uint32_t * find = (uint32_t *)(0x08080000);
	int i = 0;
	while(find[i] != 0xFFFFFFFF)
	{
		i++;
	}
	return ((uint32_t)(&(find[i])));
}

void writeToFlesh(useFlesh * data)
{
	HAL_FLASH_Unlock();
	 uint64_t next = 0;
    while(data->sizeOfData > next)
    {
    	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, data->placeInflesh + next, *(uint64_t*)(data->text + next));
    	next+=8;
    }
    HAL_FLASH_Lock();

}



