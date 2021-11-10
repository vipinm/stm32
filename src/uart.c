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
    GPIOA->CRH = 0x00000000;
    GPIOA->CRH |= (2 << 4) | (2 << 6); /* PA9 TX Alternating function output*/
    GPIOA->CRH |= (1 << 10); /* PA10 Floating input */
 #if 0
    GPIOA->CRL = 0x00000000;
    GPIOA->CRL |= (1 << 8) | (2 << 10); /* PA2 TX Alternating function output*/
    GPIOA->CRL |= (1 << 14); /* PA3 Floating input */ 
#endif

    USART1->BRR = (8000000/9600); /* BR 115200 */
 #if 0
    USART2->BRR = (8000000/9600); /* BR 115200 */
#endif

    /* USART enable */
    /* 1 start bit 8 Data bits , n stop bit */
    /* USART Tx enable */
    /* USART Rx enable */
    USART1->CR1 = 0x00000000;
    USART1->CR2 = 0x00000000;
    USART1->CR1 |= ((1 << 13) | (1 << 3) | (1 << 2));
    USART1->CR2 |= (1 << 11);/*CLKEN */
 #if 0
    USART2->CR1 = 0x00000000;
    USART2->CR2 = 0x00000000;
    USART2->CR1 |= ((1 << 13) | (1 << 3) | (1 << 2));
    USART2->CR2 |= (1 << 11);/*CLKEN */
#endif
}

void uart_tx(char *t)
{
    //REG_SET(USART1->usart_sr, 0);
    {
/*
	if(*t == '\n')
	{
            while(!(REG_GET(USART1->usart_sr) & (1 << 6))) {};
            USART1->usart_dr = '\r';
        }*/
        while(!(USART1->SR & (1 << 6))) {};
        USART1->DR = *t;
	t++;
    }

}
char uart_rx(void)
{
	char t = '\0';
	while(!(USART1->SR & (1<<5))){};
	t = USART1->DR;
	printf("%c \r\n ", t);
	return t;
}

void echo(void)
{
	int i = 0;
	char t = '\0';

        while(!(USART1->SR & (1<<5)));
        t = USART1->DR;
	/*printf("\n\r rx:%d \n", t);*/
	
        while(!(USART1->SR & (1 << 7))) ;
        USART1->DR = t;
}
