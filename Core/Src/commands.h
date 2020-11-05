#include "stm32l4xx_hal.h"


void COMMAND_Init(void);
void Process_Input(uint8_t* buffer);
void Read_Buffer(char *rxByte, uint8_t* buffer, int *bf_count);
void Write_To_Buffer(char *rxByte, uint8_t* buffer, int *bf_count, int bufferSize);
void Handle_Backspace(char *rxByte, uint8_t* buffer, int *bf_count);
void FAN_ON(void);
void FAN_OFF(void);
void FAN_20(void);
void FAN_80(void);
void PID_30(void);
void PID_60(void);
void PID_50(void);
void PID_5(void);
void PID_80(void);
void PID_75(void);
void PID_84(void);
void PID_90(void);
void PID_94(void);
