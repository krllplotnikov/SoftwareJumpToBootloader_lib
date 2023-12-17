#ifndef INC_JUMPINBOOTLOADER_H_
#define INC_JUMPINBOOTLOADER_H_
#endif /* INC_JUMPINBOOTLOADER_H_ */

#include "main.h"

#ifdef STM32F1
#define BOOTLOADER_ADDR 0x1FFFF000
#endif
#ifdef STM32G0
#define BOOTLOADER_ADDR 0x1FFF0000
#endif
#ifdef STM32F4
#define BOOTLOADER_ADDR 0x1FFF0000
#endif


void EnableSoftwareJumpToBootloader(UART_HandleTypeDef *huart);
void JumpToBootloader();


