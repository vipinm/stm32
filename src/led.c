#include <stdint.h>
#include "led.h"
#include "reg.h"

void delay(unsigned volatile int t){
    for (unsigned volatile int i = 0; i < t; i++);
}

void led_init(void)
{
     /* led at PB12 */

     REG(GPIOB_MODERH) |= ~(3 << 18);
     REG(GPIOB_MODERH) |= (1 << 16);
     
    while(1)
    {
        REG(GPIOB_ODR) ^= (1 << 12);
        delay(1000000U);
    }

}

