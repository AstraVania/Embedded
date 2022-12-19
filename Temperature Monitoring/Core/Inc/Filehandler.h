/*
 * Filehandler.h
 *
 *  Created on: 22 Nov 2022
 *      Author: student
 */

#ifndef INC_FILEHANDLER_H_
#define INC_FILEHANDLER_H_

#include <stdio.h>
#include "fatfs.h"
#include <string.h>
using namespace std;

class Filehandler
{
private:
	BYTE readBuf[100];
	FATFS FatFs;
	FIL fil;
	FRESULT fres;
    char _filename[20];
public:
	Filehandler(const char * filename)
	{
		strcpy(_filename, filename);
		HAL_Delay(1000);
		fres = f_mount(&FatFs, "", 1);
		if (fres != FR_OK)
		{
			printf("f_mount error (%i)\r\n", fres);
		}
		f_unlink(_filename);
	}
	void writeToFile(const char * data);
	void readFromFile();
    void clearSD();
};


#endif /* INC_FILEHANDLER_H_ */


