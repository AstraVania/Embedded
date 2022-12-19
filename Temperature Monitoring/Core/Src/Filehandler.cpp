
#include <Filehandler.h>




void Filehandler:: writeToFile(const char * data)
{

	 fres = f_open(&fil, _filename, FA_WRITE | FA_OPEN_ALWAYS|FA_OPEN_APPEND);
	 if(fres != FR_OK)
	 {
		 printf("f_open error (%i)\r\n", fres);
	 }
    strcpy((char*)readBuf, data);
	UINT bytesWrote;
	fres = f_write(&fil, readBuf, strlen(data), &bytesWrote);
     if(fres != FR_OK)
     {
    	 printf("f_write error\r\n");
     }
	 f_close(&fil);
}
void Filehandler:: readFromFile()
{
	  fres = f_open(&fil, _filename, FA_READ );
	  if (fres != FR_OK)
	  {
		  printf("f_open error\r\n");
	  }
	  TCHAR* rres = f_gets((TCHAR*)readBuf, 100, &fil);
	  if(rres == 0)
	  {
		  printf("f_gets error (%i)\r\n", fres);
	  }
	  f_close(&fil);

}

void Filehandler:: clearSD()
{
	f_unlink(_filename);
}
