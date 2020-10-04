#include "fan.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"

TIM_HandleTypeDef htim2;

void startFan(void){
	setPWM(htim2,TIM_CHANNEL_2,200,200);
}

void stopFan(void){
	setPWM(htim2,TIM_CHANNEL_2,200,0);

}

void fan20(void){
	setPWM(htim2,TIM_CHANNEL_2,200,40);
}

void fan80(void){
	setPWM(htim2,TIM_CHANNEL_2,200,160);
}

void setFan(int speed){
	if(speed > -1 && speed < 101){
		setPWM(htim2,TIM_CHANNEL_2,200,speed*1.25 + 75);
	}


}
