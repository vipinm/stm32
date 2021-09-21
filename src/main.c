#include <stdio.h>
#include "reg.h"
#include "main.h"
#include "led.h"
#include "uart.h"

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
    uart_tx("\n");
    led_init();
    for(;;);
}
void rcc_init()
{
    uint32_t data;

    data = REG_GET(RCC->rcc_cr);
    data |= (1 << 0) ;
    REG_SET(RCC->rcc_cr, data);

    data = REG_GET(RCC->rcc_cfgr);
    data |=((5 << 24));
    /*data &= ~(1);*/
    REG_SET(RCC->rcc_cfgr, data);

    data = REG_GET(RCC->rcc_apb2enr);
    data |=((1 << 14) | (1 << 3) | (1 << 2) | (1 << 0));
    REG_SET(RCC->rcc_apb2enr, data);
}
