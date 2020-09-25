#include "stm32l4xx_hal.h"

uint8_t Is_First_Captured;
static volatile  uint16_t Distance;

void delay (uint16_t time);

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

void HCSR04_Read (void);
uint16_t getDistance(void);
