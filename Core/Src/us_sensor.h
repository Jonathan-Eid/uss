#include "stm32l4xx_hal.h"

volatile uint32_t history_idx;
static volatile uint8_t Is_First_Captured;
static volatile  uint16_t Distance;
static volatile  uint8_t distance_history[50];

void delay (uint16_t time);

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

void HCSR04_Read (void);
uint16_t getDistance(void);
