#include "fan.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"

TIM_HandleTypeDef htim2;

void startFan(void){
	setPWM(htim2,TIM_CHANNEL_2,200,200);
}

void stopfan(void){
	setPWM(htim2,TIM_CHANNEL_2,200,0);

}
void setFan(int speed){
	if(speed > -1 && speed < 101){
		setPWM(htim2,TIM_CHANNEL_2,200,speed*1.25 + 75);
	}


}
