#include "UART.h"
#include "us_sensor.h"
#include "fan.h"
#include "pid.h"
#include "led_state.h"

#include <string.h>
#include <stdio.h>

//Set boolean values indicating
//Whether the LEDs should be flashing

//Red LED Flash State
static int PID_LOOP=0;
volatile static int READ_COUNT=0;

void COMMAND_Init(void){
	//Set buffer size of command input
	int bufferSize = 20;

	//Create buffer array
	uint8_t buffer[bufferSize];

	//Counter to load read value into buffer index
	int bf_count = 0;

	//Start command input loop
	setFan(100);

 	 set_P(-0.9);
 	 set_I(0.0025);
 	 set_D(-1);
 	 //set_P(-0.87);
 	 //set_I(-0.006);
 	 //set_D(-1.3);

 	 while(1){
 		//Read byte and save
 		char rxByte = USART_Read(USART2);
		//Pass byte, buffer, and count to helper functions
		Read_Buffer(&rxByte, buffer, &bf_count);
		Handle_Backspace(&rxByte, buffer, &bf_count);
		Write_To_Buffer(&rxByte, buffer, &bf_count, bufferSize);

	  	 HCSR04_Read();
	  	 HAL_Delay(100);
	  	 uint16_t distance = getDistance();
	  	 setState(distance);

		 if(PID_LOOP){

	 	  	 int pwm = calcFan(distance);
	 	  	 setFan(pwm);
		 }
		 if(READ_COUNT==20){
		 	  	char str[12];
		 		 sprintf(str, "%d", distance);
		 		 USART_Write(USART2, (uint8_t*)"Position: ", 10);
		 		 USART_Write(USART2, (uint8_t*)str, 4);
		 		 USART_Write(USART2, (uint8_t*)"cm", 2);
		 		 USART_Write(USART2, (uint8_t*)"\r\n", 2);
		 		 READ_COUNT=0;
		 }
		 READ_COUNT++;

 	 }

}

//After passing in a buffer, check if the bytes represent a valid command
void Process_Input(uint8_t* buffer){
	char* invalid_msg = "Invalid command\r\n";
	char* command = (char*) buffer;

	//Handle input commands
	if(strcmp(command, "FANON") == 0){
				FAN_ON();
				USART_Write(USART2, (uint8_t*)"FAN 100%\r\n", 11);
	}else if(strcmp(command, "FANOFF") == 0){
				FAN_OFF();
				USART_Write(USART2, (uint8_t*)"FAN Off\r\n", 11);
	}else if(strcmp(command, "FAN20") == 0){
				FAN_20();
				USART_Write(USART2, (uint8_t*)"FAN 20%\r\n", 11);
	}else if(strcmp(command, "FAN80") == 0){
				FAN_80();
				USART_Write(USART2, (uint8_t*)"FAN 80%\r\n", 11);
	}else if(strcmp(command, "PID30") == 0){
		PID_30();
		USART_Write(USART2, (uint8_t*)"PID 30\r\n", 11);
	}else if(strcmp(command, "PID60") == 0){
		PID_60();
		USART_Write(USART2, (uint8_t*)"PID 60\r\n", 11);
	}else if(strcmp(command, "PID5") == 0){
		PID_5();
		USART_Write(USART2, (uint8_t*)"PID 5\r\n", 11);
	}else if(strcmp(command, "PID50") == 0){
		PID_50();
		USART_Write(USART2, (uint8_t*)"PID 50\r\n", 11);
	}else if(strcmp(command, "PID80") == 0){
		PID_80();
		USART_Write(USART2, (uint8_t*)"PID 80\r\n", 11);
	}else if(strcmp(command, "PID75") == 0){
		PID_75();
		USART_Write(USART2, (uint8_t*)"PID 75\r\n", 11);
	}else if(strcmp(command, "PID84") == 0){
		PID_84();
		USART_Write(USART2, (uint8_t*)"PID 84\r\n", 11);
	}else if(strcmp(command, "PID90") == 0){
		PID_90();
		USART_Write(USART2, (uint8_t*)"PID 90\r\n", 11);
	}else if(strcmp(command, "PID94") == 0){
		PID_94();
		USART_Write(USART2, (uint8_t*)"PID 94\r\n", 11);
	}else{
				USART_Write(USART2, (uint8_t*)invalid_msg,20);
	}

}

void FAN_ON(void){
	PID_LOOP=0;
	startFan();
}

void FAN_OFF(void){
	PID_LOOP=0;
	stopFan();

}

void FAN_20(void){
	PID_LOOP=0;
	fan20();
}

void FAN_80(void){
	PID_LOOP=0;
	fan80();
}

void PID_30(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(30);
	PID_LOOP=1;
}

void PID_60(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(60);
	PID_LOOP=1;
}

void PID_5(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(5);
	PID_LOOP=1;
}
void PID_50(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(50);
	PID_LOOP=1;
}

void PID_80(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(80);
	PID_LOOP=1;
}

void PID_75(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(75);
	PID_LOOP=1;
}

void PID_84(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(84);
	PID_LOOP=1;
}

void PID_90(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(90);
	PID_LOOP=1;
}

void PID_94(void){
	PID_LOOP=1;
	clearPID();
	setFan(100);
 	HAL_Delay(1000);
	setPoint(94);
	PID_LOOP=1;
}



void Read_Buffer(char* rxByte, uint8_t* buffer, int *bf_count){

		//Set string used to write out new line
		char newLineStr[] = "\r\n";

		//If a carriage return is read, write a new line and process the preceding command
		if(*rxByte == '\r'){
			USART_Write(USART2,(uint8_t *)newLineStr,2);
			buffer[*bf_count] = '\0';
			Process_Input(buffer);
			memset(buffer, 0, sizeof(&buffer));
			*bf_count = 0;
		}
}

void Write_To_Buffer(char* rxByte, uint8_t* buffer, int *bf_count, int bufferSize){
		//Add every character that isn't a new line or backspace/delete input to the buffer if the buffer isn't full
		if(*rxByte != 0 & *bf_count < bufferSize & *rxByte !='\r' & *rxByte !='\b' & *rxByte != 127){
			buffer[*bf_count] = *rxByte;
			USART_Write(USART2, (uint8_t*)rxByte,1);
			*bf_count = *bf_count + 1;
		}
}

void Handle_Backspace(char* rxByte, uint8_t* buffer, int* bf_count){

		//If a delete key was read, write the input on the frontend but delete the previous index in the buffer and decerement the counter
		if(*rxByte == 127 & bf_count > 0){
			USART_Write(USART2,(uint8_t*) rxByte,1);
			*bf_count = *bf_count - 1;
			buffer[*bf_count] = 0;
		}
}
