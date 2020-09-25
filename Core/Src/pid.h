
#include "stm32l4xx_hal.h"

double Kp;
double Ki;
double Kd;
int point;

void setPoint(int p);
int calcFan(uint16_t distance, int *integral, int *derivative, int *last_error);
