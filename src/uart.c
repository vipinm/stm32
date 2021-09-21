#include "uart.h"

/*Procedure:
	1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	2. Program the M bit in USART_CR1 to define the word length.
	3. Program the number of stop bits in USART_CR2.
	4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take place. Configure the DMA register as explained in multibuffer communication.
	5. Select the desired baud rate using the USART_BRR register.
	6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this for each data to be transmitted in case of single buffer.
	8. After writing the last data into the USART_DR register, wait until TC=1. This indicates that the transmission of the last frame is complete. This is required for instance when
	   the USART is disabled or enters the Halt mode to avoid corrupting the last transmission. */

void uart_init(void)
{
    /* PA9 TX: alternate function push-pull , 
       PA10 RX: input floating/input pull-up  */

    REG(GPIOA_MODERH) |= (3 << 4); /* PA9 output mode */
    REG(GPIOA_MODERH) |= (2 << 6); /* PA9  alt function push-pull */
    REG(GPIOA_MODERH) |= (2 << 10);/* PA10 alternate function push-pull */ 
    /*REG(USART1_CR1) &= ~(1 << 12);*/ /* word length : 1 start bit , 8 data bits*/
    /*REG(USART1_CR2) &= ~(3 << 12); *//* stop bits: 1 stop bit */
    REG(USART1_BRR) |= (72000000U / 9600U ); /* BR 9600 bits/s */
    REG(USART1_CR1) |= ((1 << 13) | (1 << 3) | (1<< 2)); /* USART enable */
}

void uart_tx(char *t)
{
    REG(USART1_DR) |= *t;
    while(1)
    {
        if(REG(USART1_SR) & (1 << 6))
            break;
    }
}
