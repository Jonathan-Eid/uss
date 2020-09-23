#include "stm32l4xx_hal.h"


void delay (uint16_t time);

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

uint8_t HCSR04_Read (void);
