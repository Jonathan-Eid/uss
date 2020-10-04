
#include "stm32l4xx_hal.h"

double Kp;
double Ki;
double Kd;
int point;

void set_P(float p);
void set_I(float i);
void set_D(float d);
void setPoint(int p);
void clearPID(void);

int calcFan(uint16_t distance);
