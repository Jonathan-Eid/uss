#include "stm32l4xx_hal.h"



void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,uint16_t pulse);
void stopPWM(TIM_HandleTypeDef timer, uint32_t channel);
void startPWM(TIM_HandleTypeDef timer, uint32_t channel);

