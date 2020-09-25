
#include "stm32l4xx_hal.h"

double Kp;
double Ki;
double Kd;
int point;

void set_P(float p);
void set_I(float i);
void set_D(float d);
void setPoint(int p);

int calcFan(uint16_t distance, int *integral, int *derivative, int *last_error);
