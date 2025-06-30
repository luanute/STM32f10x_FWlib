#ifndef ___UART_REG_H__
#define ___UART_REG_H__
//#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include "gpio_reg.h"
#include "get_clk.h"
#include <stdio.h>

typedef enum {
	Pins_PA9PA10,	//USART1
	Pins_PB6PB7,	////USART1
	Pins_PA2PA3,	//USART2
	Pins_PD5PD6,	//USART2
	Pins_PB10PB11,	//USART3
	Pins_PC10PC11,	//USART3//UART4
	Pins_PD8PD9,	//USART3
	Pins_PA0PA1,	//UART4
	Pins_PC12PD2,	//UART5
	Pins_PC6PC7,	//USART6
	Pins_PG14PG9,	//USART6
	Pins_PB8PE7,	//UART7
	Pins_PF7PF6,	//UART7
	Pins_PE1PE0		//UART8
} Pins_USART;

typedef void (*data_uart_handle_t)(char * data);
static data_uart_handle_t data_uart_ptr = NULL;
static volatile char rx_buffer[100];
static volatile uint16_t buffer_index = 0;

void USARTx_INIT(USART_TypeDef *USARTx,Pins_USART Pinx,uint32_t Baud);
void USARTx_Write_C(USART_TypeDef *USARTx, char data);
void USARTx_Write_S(USART_TypeDef *USARTx, char * data);
char USARTx_READ(USART_TypeDef *USARTx);
void USART1_IRQHandler(void);
void USART_RX_Data_set_callback(data_uart_handle_t cb);

#endif
