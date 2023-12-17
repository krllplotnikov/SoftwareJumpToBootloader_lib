#include <SoftwareJumpToBootloader.h>

UART_HandleTypeDef *m_huart;
uint8_t bootMessage[1] = {};

void EnableSoftwareJumpToBootloader(UART_HandleTypeDef *huart){
	m_huart = huart;
	HAL_UART_Receive_IT(m_huart, bootMessage, 1);
}

void JumpToBootloader(){
    void (*SysMemBootJump)(void);
    volatile uint32_t addr = BOOTLOADER_ADDR;
    HAL_RCC_DeInit();
    HAL_DeInit();

    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    __disable_irq();
#if defined(STM32F4) || defined(STM32G0)
    __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
#endif
    SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));
    __set_MSP(*(uint32_t *)addr);
    SysMemBootJump();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == m_huart)
    {
  	  if(bootMessage[0] == 0x7F)
  		JumpToBootloader();
  	  else
  		  HAL_UART_Receive_IT(m_huart, bootMessage, 1);
    }
}
