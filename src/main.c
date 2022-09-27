//#include <stdio.h>
#include "reg.h"
#include "main.h"
#include "led.h"
#include "uart.h"

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t REMAP;
	volatile uint32_t COMP[3];
}FPB_type;

FPB_type *const FPB = (FPB_type *)0xE0002000;
void rcc_init(void);

int main(void)
{
    char t;
    rcc_init();
    uart_init();
    printf("\r\n FPB_CTRL : %d \r\n", FPB->CTRL);
    printf("revision : %d \r\n", ((FPB->CTRL >> 28) & 0xF));
    printf("num_code : %d \r\n", ((((FPB->CTRL >> 12) & 0x7) << 4) | ((FPB->CTRL >> 4) & 0xF)));

    printf("\r\n RCC_CR : 0x%x \r\n", RCC->CR);
    /*led_init();*/
    while(1)
    {
	   echo();
    }
}
void rcc_init()
{
    RCC->APB2RSTR = 0x00000000;
    RCC->APB1RSTR = 0x00000000;
    RCC->AHBENR   = 0x00000000;
    RCC->APB2ENR = 0x00000000;
    RCC->APB1ENR = 0x00000000;
    RCC->CFGR    &= 0xF8FF0000;
    RCC->CR      &= 0xFEF6FFFF;
    RCC->CR      &= 0xFFFBFFFF;
    RCC->CFGR    &= 0xFF80FFFF;
    RCC->CIR     &= 0x00000000;

    /*RCC->CR      |= (1 << 0);*//* HSION */
    RCC->CFGR    |= (5 << 24);/* Microcontroller clock output (HSI clck) */
    RCC->APB2ENR |= (1 << 14); /* USART1EN */
    RCC->APB1ENR |=((1 << 17)); /* USART2EN */
    RCC->APB2ENR |= ((1 << 2) | (1));/* IOPAEN AFIOEN */
}
