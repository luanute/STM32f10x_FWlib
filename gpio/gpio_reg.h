#ifndef ___GPIO_REG_H__
#define ___GPIO_REG_H__
#include "stm32f10x.h"
//bitbanding
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long*)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

//Dia chi
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//IO
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //ngo ra
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //ngo vao

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //ngo ra
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //ngo vao


// ennable clock cho port GPIO
#define RCC_GPIOA_EN RCC->APB2ENR|=(1<<2)
#define RCC_GPIOB_EN RCC->APB2ENR|=(1<<3)
#define RCC_GPIOC_EN RCC->APB2ENR|=(1<<4)
#define RCC_GPIOD_EN RCC->APB2ENR|=(1<<5)
#define RCC_GPIOE_EN RCC->APB2ENR|=(1<<6)
#define RCC_GPIOF_EN RCC->APB2ENR|=(1<<7)
#define RCC_GPIOG_EN RCC->APB2ENR|=(1<<8)
#define RCC_GPIOH_EN RCC->APB2ENR|=(1<<9)


// GPIO control Setting 
#define INPUT_ANALOG             ((uint8_t) 0x00)
#define INPUT_FLOATING           ((uint8_t) 0x01)
#define INPUT_PUPD               ((uint8_t) 0x02)

#define OUTPUT_PP 							 ((uint8_t) 0x00)
#define OUTPUT_OD 							 ((uint8_t) 0x01)
#define OUTPUT_AF_PP 						 ((uint8_t) 0x02)
#define OUTPUT_AF_OD 						 ((uint8_t) 0x03)

#define NO_PULL                  ((uint8_t) 0x00)
#define PULL_UP                  ((uint8_t) 0x01)
#define PULL_DW                  ((uint8_t) 0x02)


#define MODE_INPUT  						 ((uint8_t) 0x00)
#define MODE_OUTPUT_10M          ((uint8_t) 0x01)
#define MODE_OUTPUT_2M           ((uint8_t) 0x02)
#define MODE_OUTPUT_50M          ((uint8_t) 0x03)

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin);
void GPIO_Write(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin, uint8_t State );
uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin);
void GPIOx_INIT(GPIO_TypeDef *GPIOx, uint8_t GPIO_Pin, uint8_t Mode, uint8_t Pull, uint8_t Speed);
#endif
