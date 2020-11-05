#include "led_state.h"
#include "LED.h"
#include "stm32l4xx_hal.h"

int no_state = 0;
int green_state = 0;
int yellow_state = 0;
int red_state = 0;
int warning_state = 0;
int warning_counter = 0;

void setState(uint16_t distance){
	if(distance < 70 && !no_state){
		chooseState(-1);
	}
	if(distance > 70 && distance < 80 && !green_state){
		chooseState(0);
	}
	if(distance > 80 && distance < 88 && !yellow_state){
		chooseState(1);
	}
	if(distance > 88 && distance < 92 && !red_state){
		chooseState(2);
	}
	if(distance > 92 && !warning_state){
		chooseState(3);
	}
	if(distance > 92 && warning_state){
		warning_counter++;
		warningToggle(warning_counter);
	}
}

void chooseState(int state){

	no_state = 0;
	green_state = 0;
	yellow_state = 0;
	red_state = 0;
	warning_state = 0;
	warning_counter = 0;

	if(state == -1){
		no_state = 1;
		Red_LED_Off();
		Green_LED_Off();

	}
	if(state == 0){
		green_state = 1;
		Red_LED_Off();
		Green_LED_On();
	}
	if(state == 1){
		yellow_state = 1;
		Red_LED_On();
		Green_LED_On();
	}
	if(state == 2){
		red_state = 1;
		Red_LED_On();
		Green_LED_Off();
	}
	if(state == 3){
		Red_LED_Off();
		Green_LED_Off();
		warning_state = 1;
	}
}

void warningToggle(int counter){
	if(counter % 2 == 0){
		Red_LED_Toggle();
	}
}
