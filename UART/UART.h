#ifndef _UART_H_
#define _UART_H_

#include "../include.h"
//BaseAddress
#define UART0	UART0_BASE
#define UART1	UART1_BASE
#define UART2	UART2_BASE
#define UART3	UART3_BASE
#define UART4	UART4_BASE
#define UART5	UART5_BASE
#define UART6	UART6_BASE
#define UART7	UART7_BASE
//Parity Bit
#define None 	0x00	// No parity
#define Even    0x06  	// Even parity
#define Odd     0x02  	// Odd parity
#define One     0x82  	// Parity bit is one
#define Zero    0x86  	// Parity bit is zero
//Error define
#define ERROR_NONE			0
#define INVALID_UART_NAME	1
#define INVALID_DATA_BITS	2
#define INVALID_PARITY_BIT	3
#define INVALID_STOP_BIT	4

#define BAD_COMMAND		0x01
#define CmdRequest	0x02

typedef struct
{
		unsigned long PortName;
		unsigned long BaudRate;
		unsigned char DataBits;
		unsigned char Parity;
		unsigned char StopBits;
		void (*ISR)(void);
}UARTType;

//typedef void (*pfnCmdLine)(void);

typedef struct
{
    //
    //! A pointer to a string containing the name of the command.
    //
    const char *pcCmd;

    //
    //! A function pointer to the implementation of the command.
    //
    void (*pfnCmd)(void);

    //
    //! A pointer to a string of brief help text for the command.
    //
    const char *pcHelp;
}
tCmdLineEntry;

unsigned char ConfigUART(UARTType *UART);
uint16_t recv_UART0(uint8_t* rxBuf, uint16_t numToRead, bool block);
void UART0_Handler();
void UARTPutNum(uint32_t UART_Base, long Num);
void UARTStringPut(uint32_t ui32Base,const uint8_t* s);
uint16_t ReadRxBuffer_recv_UART0(uint8_t* rxBuf, uint16_t numToRead);
uint16_t GetRxData(uint8_t *data, uint16_t len);
void UARTPrint_num( int32_t num);

#endif /* SEFT_BACLANCING_ROBOT_MYUART_H_ */
