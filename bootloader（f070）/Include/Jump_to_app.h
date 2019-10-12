#ifndef __JUMP_TO_APP_H
#define __JUMP_TO_APP_H
#include "Include.h"


#define FLAG_FLASH_ADDRESS   0x0801FC00   //stm32f070
#define APP_FLASH_ADDRESS    0x08002800    //10KB
#define BOOT_TO_APP          1
#define APP_TO_BOOT          2
void Jump(void);
#endif

