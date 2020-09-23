#ifndef __STM32L476G_DISCOVERY_CLOCK_H
#define __STM32L476G_DISCOVERY_CLOCK_H

#include "stm32l476xx.h"

void SysTick_Init(uint32_t ticks);
int SysTick_Reloaded(void);
void SysTick_Wait(void);
void Delay (uint32_t nTime);

#endif /* __STM32L476G_DISCOVERY_DMA_H */


