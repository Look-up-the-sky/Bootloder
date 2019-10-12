#ifndef __FLASH_H
#define __FLASH_H
#include "Include.h"

#define MAX_DATA_LEN         236
#define MAX_WORD_LEN         59


INT8U Flash_Update(void);
INT8U Flash_Erase(void);
#endif
