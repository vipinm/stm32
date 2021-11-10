#include <stdint.h>
#include "led.h"
#include "reg.h"

void delay(unsigned volatile int t){
    for (unsigned volatile int i = 0; i < t; i++);
}

void led_init(void)
{
    uint32_t data =0;

     /* led at PB12 */
    data = REG_GET(GPIOB->CRH);
    data &= (~(3 << 18));
    data |= (1 << 16);
    data = REG_SET(GPIOB->CRH, data);
    while(1)
    {
        REG(GPIOB_ODR) ^= (1 << 12);
        delay(1000000U);
    }
}

