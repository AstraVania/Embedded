

#include <Flash.h>


startup  newstartup;

Flash::~Flash() {
	// TODO Auto-generated destructor stub
}

void  Flash:: eraseFromFlash()
{
	uint32_t ERORR;
	HAL_FLASHEx_Erase(&myflesh , &ERORR);
}

void  Flash:: writeToFlesh(uint32_t crit , uint32_t warning)
{
	HAL_FLASH_Unlock();
	eraseFromFlash();
	uint64_t next = 0;

	newstartup.MagicNumber = 0xABC;
	newstartup.startCrit = crit;
	newstartup.startWarninng = warning;
	uint64_t * data = (uint64_t *)&newstartup;

	while(sizeOfData > next)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, placeInflesh + next, *data++);
		next+=8;
	}
	HAL_FLASH_Lock();
}
