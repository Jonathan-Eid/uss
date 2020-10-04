#include "pid.h"

double Kp = 0;
double Ki = 0;
double Kd = 0;
int point = 0;
int integral = 0;
int derivative = 0;
int last_error = 0;

void set_P(float p){
	Kp = p;
}

void set_I(float i){
	Ki = i;
}

void set_D(float d){
	Kd = d;
}

void setPoint(int p){
	point = p;
}

void clearPID(void){
	integral = 0;
	derivative = 0;
	last_error = 0;
}

int calcFan(uint16_t distance){

	int error = point - distance;
	integral = integral + error;
	derivative = error - last_error;

	int pwm = ((Kp * error) + (Ki * integral ) + (Kd * derivative));

	if(pwm > 100){
		pwm = 100;
	}else if (pwm < 0){
		pwm = 0;
	}

	last_error = error;

	return pwm;


}
