#include "LED.h"
#include "UART.h"
#include "commands.h"
#include "SysDelay.h"

#include <string.h>
#include <stdio.h>

//Set boolean values indicating
//Whether the LEDs should be flashing

//Red LED Flash State
static int R_Flash = 0;

//Green LED Flash State
static int G_Flash = 0;

void COMMAND_Init(void){
	//Set buffer size of command input
	int bufferSize = 10;
	
	//Create buffer array
	uint8_t buffer[bufferSize];
	
	//Counter to load read value into buffer index
	int bf_count = 0;

	//Start command input loop
	while (1){
		
		//Read byte and save
		char rxByte = USART_Read(USART2);
		
		//Pass byte, buffer, and count to helper functions
		Read_Buffer(&rxByte, buffer, &bf_count);
		Handle_Backspace(&rxByte, buffer, &bf_count);
		Write_To_Buffer(&rxByte, buffer, &bf_count, bufferSize);
			
		//Wait for system tick to reload
		Delay(1);
		
		//Update Flash Counters
		Red_Flash_Counter();
		Green_Flash_Counter();

}
}



//After passing in a buffer, check if the bytes represent a valid command
void Process_Input(uint8_t* buffer){
	char* invalid_msg = "Invalid command\r\n";
	char* command = (char*) buffer;	
	
	//Handle input commands
	if(strcmp(command, "RON") == 0){
				RED_ON();
				USART_Write(USART2, (uint8_t*)"Red LED On\r\n", 16);
	}else if(strcmp(command, "ROFF") == 0){
				RED_OFF();
				USART_Write(USART2, (uint8_t*)"Red LED Off\r\n", 16);
	}else if(strcmp(command, "GON") == 0){
				GREEN_ON();
				USART_Write(USART2, (uint8_t*)"Green LED On\r\n", 16);
	}else if(strcmp(command, "GOFF") == 0){
				GREEN_OFF();
				USART_Write(USART2, (uint8_t*)"Green LED Off\r\n", 16);
	}else if(strcmp(command, "RFLASH") == 0){
				R_Flash=1;
				USART_Write(USART2, (uint8_t*)"Red LED Flashing\r\n", 20);
	}else if(strcmp(command, "GFLASH") == 0){
				G_Flash=1;
				USART_Write(USART2, (uint8_t*)"Green LED Flashing\r\n", 24);
	}else if(strcmp(command, "FLASHOFF") == 0){
				Flash_Off();
				USART_Write(USART2, (uint8_t*)"Stopped Flashing\r\n", 20);
	}else{
				USART_Write(USART2, (uint8_t*)invalid_msg,20);
	}
	
}

//Turn Red LED on, override flashing state if the flag is on
void RED_ON(void){

	//Only if the red LED were already flashing, turn them off
	if(R_Flash){
		Red_LED_Off();
	}
	//Reset flags
		R_Flash=0;
		Red_LED_On();
}

//Turn GREEN LED on, override flashing state if the flag is on
void GREEN_ON(void){
	if(G_Flash){
		Red_LED_Off();
	}
	//Reset flags
		G_Flash=0;
		Green_LED_On();
}

//Set flashing flag off and turn the Red LED off
void RED_OFF(void){
				R_Flash=0;
				Red_LED_Off();
}

//Set flashing flag off and turn the Red LED off
void GREEN_OFF(void){
				G_Flash=0;
				Green_LED_Off();
}

//Loop red flash counter if flag is on
void Red_Flash_Counter(void){
	static int r_loop = 0;
	if(r_loop == 1000){
		Red_LED_Toggle();
		r_loop = 0;
	}else if (R_Flash){
		r_loop++;
	}else if (R_Flash == 0){
		r_loop = 0; 
	}
}

//Loop green flash counter if flag is on
void Green_Flash_Counter(void){
	static int g_loop = 0;
	if(g_loop == 1000){
		Green_LED_Toggle();
		g_loop = 0;
	}else if (G_Flash){
		g_loop++;
	}else if (G_Flash == 0){
		g_loop = 0; 
	}
}


//Flash off helper
void Flash_Off(void){

	//Only if the lights were already flashing, turn them off
	if(R_Flash){
		Red_LED_Off();
	}
	if(G_Flash){
		Green_LED_Off();
	}
	//Reset flags
		R_Flash=0;
		G_Flash=0;
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
