#include "pid.h"

double Kp = -0.8;
double Ki = 0;
double Kd = 0;
int point = 50;
int control_variable = 0;




int calcFan(uint16_t distance, int* integral, int* derivative, int* last_error){

	int error = point - distance;
	*integral = *integral + error;
	*derivative = error - *last_error;

	int pwm = ((Kp * error) + (Ki * *integral ) + (Kd * *derivative));

	if(pwm > 100){
		pwm = 100;
	}else if (pwm < 0){
		pwm = 0;
	}

	*last_error = error;

	return pwm;


}
