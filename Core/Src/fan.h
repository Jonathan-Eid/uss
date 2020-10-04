#include "pwm.h"


TIM_HandleTypeDef htim2;

void startFan(void);
void stopFan(void);
void setFan(int speed);
void fan20(void);
void fan80(void);
