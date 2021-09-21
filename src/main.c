#include<stdio.h>
#include "main.h"
#include "led.h"
#include "uart.h"
#include "reg.h"

void rcc_init(void);

int main(void)
{
    rcc_init();
    uart_init();
    uart_tx("S");
    uart_tx("H");
    uart_tx("I");
    uart_tx("V");
    uart_tx("A");
    led_init();
    for(;;);
}
void rcc_init()
{
    REG(FLASH_ACR) |= 2;  
    REG(RCC_CR) |= (1 << 16);
    REG(RCC_CR) &= 0xfffffffe;
    REG(RCC_CFGR) |= (1 << 16);
    REG(RCC_APB2ENR) |= ((1 << 14) | (1 << 3) | (1 << 2) | (1));/* USART1EN IOPBEN */
}
