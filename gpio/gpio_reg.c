#include "gpio_reg.h"


void GPIOx_INIT(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin, uint8_t Mode, uint8_t Pull, uint8_t Speed ){
    if(GPIOx == GPIOA){RCC_GPIOA_EN;}
		else if(GPIOx == GPIOB){RCC_GPIOB_EN;}
		else if(GPIOx==GPIOC){RCC_GPIOC_EN;}
		else if(GPIOx==GPIOD){RCC_GPIOD_EN;}
		else if(GPIOx==GPIOE){RCC_GPIOE_EN;}
		
		if(GPIO_Pin <8){
	     	GPIOx->CRL&=~(0xF<<(GPIO_Pin*4));
	      GPIOx->CRL|=(((Mode<<2)+Speed)<<(GPIO_Pin*4));
		}else{
	     GPIOx->CRH&=~(0xF<<(GPIO_Pin*4));
	     GPIOx->CRH|=(((Mode<<2)+Speed)<<((GPIO_Pin-8)*4));
		}
	  
		if(Pull==PULL_UP){
		  GPIOx->ODR|= (1<<GPIO_Pin);
		}	else{
		  GPIOx->ODR &=~(1<<GPIO_Pin);
		}
}

void GPIO_Write(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin, uint8_t State ){
      if(State){	GPIOC->BSRR|=(1<<GPIO_Pin);}
			else{GPIOx->BSRR|=(1<<(GPIO_Pin+16));}
}

uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin) {
	return (((GPIOx->IDR)&(1<<GPIO_Pin)) == 0)? 0:1;
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin){
      GPIOx->ODR ^= (1<<GPIO_Pin);
}
