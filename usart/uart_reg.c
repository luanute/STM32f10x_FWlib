#include "uart_reg.h"
	

void USARTx_INIT(USART_TypeDef *USARTx,Pins_USART Pinx,uint32_t Baud)
{
	float USART_DIV=0;
	uint16_t fraction=0;
	uint16_t mantissa=0;
	uint32_t PCLKx;
	uint32_t Boud=0;
	
	//ENABLE RCC
	RCC->APB2ENR |= 1<<0; //AFIO
	
	if(USARTx==USART1) 
	{
		RCC->APB2ENR |= (1<<14);
		PCLKx=Get_PCLK2_Frequency(); 
	}
	else if(USARTx==USART2) 
	{
		RCC->APB1ENR |= (1<<17);
		PCLKx=Get_PCLK1_Frequency();
	}
	else if(USARTx==USART3) 
	{
		RCC->APB1ENR |= (1<<18);
		PCLKx=Get_PCLK1_Frequency();
	}
	
	//PIN CONFIG
	if(Pinx==Pins_PA9PA10) 
	{
		GPIOx_INIT(GPIOA,9,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOA,10,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	else if (Pinx==Pins_PB6PB7)
	{
		AFIO->MAPR|=(1<<2);
		GPIOx_INIT(GPIOB,6,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOB,7,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	else if (Pinx==Pins_PA2PA3)
	{
		GPIOx_INIT(GPIOA,2,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOA,3,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	else if (Pinx==Pins_PD5PD6)
	{
		AFIO->MAPR|=(1<<3);
		GPIOx_INIT(GPIOD,5,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOD,6,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	else if (Pinx==Pins_PB10PB11)
	{
		GPIOx_INIT(GPIOB,10,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOB,11,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	else if (Pinx==Pins_PC10PC11)
	{
		GPIOx_INIT(GPIOC,10,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOC,11,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	else if (Pinx==Pins_PD8PD9)
	{
		GPIOx_INIT(GPIOD,8,OUTPUT_AF_PP,NO_PULL,MODE_OUTPUT_50M);
		GPIOx_INIT(GPIOD,9,INPUT_FLOATING,NO_PULL,MODE_INPUT);
	}
	
	//baud rate PCLK1 cho usart234, pclk2 cho usart1
	USART_DIV=PCLKx/(Baud*16);
	mantissa=(uint16_t) (USART_DIV);
	fraction=(uint16_t)((USART_DIV-mantissa)*16);
	Boud = (uint32_t)((mantissa<<4)+fraction);
	USARTx->BRR &= 0x0; //delete old baud rate
	USARTx->BRR |= Boud; //set new baud rate
	
	USARTx->CR1 |= 0<<12; //8 bit data
	USARTx->CR1 |= 0<<10; //disable parity bit
	USARTx->CR1 |= 1<<13; //usart enable
	USARTx->CR1 |= 1<<2; //read enable
	USARTx->CR1 |= 1<<3; //receive enable
	USARTx->CR2 &= ~(3<<12); //delete old stop bits
 	USARTx->CR2 |= 0<<12; //config 1 stop bits
	
	USARTx->CR1 |= 1<<5; //enable receive interrupt
	if(USARTx==USART1)
		NVIC_EnableIRQ(USART1_IRQn);
	else if (USARTx==USART2)
		NVIC_EnableIRQ(USART2_IRQn);
	else if (USARTx==USART3)
		NVIC_EnableIRQ(USART3_IRQn);

}

void USARTx_Write_C(USART_TypeDef *USARTx, char data)
{
	while(!(USARTx->SR&(1<<7)));
	USARTx->DR = data;
	while(!(USARTx->SR&(1<<6)));
}

void USARTx_Write_S(USART_TypeDef *USARTx, char * data){
	while(*data){
		USARTx_Write_C(USARTx,*data++);
	}
}

 char USARTx_READ(USART_TypeDef *USARTx)
{
	while(!(USARTx->SR&(1<<5)));
	return (char) (USARTx->DR);
}


void USART1_IRQHandler(void)
{
	 if(USART1->SR&(1<<5)){
      char rx_char = USART1->DR;  
		  if (rx_char == '\n' || rx_char == '\r') { 
            rx_buffer[buffer_index] = '\0';  
            buffer_index = 0;  // Reset index 
		    //USARTx_Write_S(USART1,(char *)rx_buffer);
			data_uart_ptr((char *)rx_buffer);
					 
        } else {
            if (buffer_index < 100 - 1) {  
                rx_buffer[buffer_index++] = rx_char;
            }
        }
			}

}

void USART_RX_Data_set_callback(data_uart_handle_t cb){
	if(cb){
	data_uart_ptr = cb;
	}
}

