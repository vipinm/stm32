#include "reg.h"
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
    uint32_t data = 0;

    /* PA9 output mode */
    /* PA9 output mode */
    /* PA9  alt function push-pull */
    /* PA10 input mode*/
    /* PA10 alternate function push-pull */
    data = REG_GET(GPIOA->gpio_crh);
    data &= (~(0xff << 4));
    data |= ((3 << 4)| (2 << 6) | (1 << 10));
    REG_SET(GPIOA->gpio_crh, data);
/*
    data = REG_GET(AFIO->afio_evcr);
    data = 0xa;
    REG_SET(AFIO->afio_evcr, data);*/


    data = (8000000/9600);
    REG_SET(USART1->usart_brr, data); /* (72000000U / 9600U ); BR 9600 bits/s */

    data = REG_GET(USART1->usart_cr1);
    /* USART enable */
    /* 1 start bit 8 Data bits , n stop bit */
    /* USART Tx enable */
    /* USART Rx enable */
    data = ((1 << 13)| (1 << 3) | (1 << 2));
    data &= (~( 1 << 12));
    REG_SET(USART1->usart_cr1, data);

    data = REG_GET(USART1->usart_cr2);
    data |= (1 << 11);
    REG_SET(USART1->usart_cr2, data);

}

void uart_tx(unsigned char *t)
{
    REG_SET(USART1->usart_sr, 0);
    /*while(!(REG_GET(USART1->usart_sr) & (1 << 7)));*/
    USART1->usart_dr = *t;

    while(!(REG_GET(USART1->usart_sr) & (1 << 6)));
}
