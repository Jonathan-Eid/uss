

#include "stm32l476xx.h"


void COMMAND_Init(void);
void Process_Input(uint8_t* buffer);
void Red_Flash_Counter(void);
void Green_Flash_Counter(void);
void Read_Buffer(char *rxByte, uint8_t* buffer, int *bf_count);
void Write_To_Buffer(char *rxByte, uint8_t* buffer, int *bf_count, int bufferSize);
void Handle_Backspace(char *rxByte, uint8_t* buffer, int *bf_count);
void Flash_Off(void);
void RED_ON(void);
void GREEN_ON(void);
void RED_OFF(void);
void GREEN_OFF(void);
