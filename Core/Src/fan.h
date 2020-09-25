#include "pwm.h"


TIM_HandleTypeDef htim2;

void startFan(void);
void stopfan(void);
void setFan(int speed);
