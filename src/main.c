//#include <stdio.h>
#include "reg.h"
#include "main.h"
#include "led.h"
#include "uart.h"

#define LOG printf

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t REMAP;
	volatile uint32_t COMP[3];
}FPB_type;

/*FPB_type *const FPB = (FPB_type *)0xE0002000;*/
void rcc_init(void);
int debug_enable(void);
static int prv_issue_breakpoint(void);
int global_test = 10;
char * getpacket();

int main(void)
{
    char *t;
    rcc_init();
    uart_init();
    LOG(" \r\n***************************************************************** \n");
    LOG(" \r\n*               Cortex M3 SDK   V 0.0                           * \n");
    LOG(" \r\n***************************************************************** \n");

    debug_enable();

    prv_issue_breakpoint();

    printf("DEbug test done 1\n");
    printf("DEbug test done 2\n");
    printf("DEbug test done 3\n");
    printf("DEbug test done 4\n");
    printf("DEbug test done 5\n");
#if 1
    /*led_init();*/
    while(1)
    {
	int i = 0;
	t = getpacket();
	for(i = 0; i < 6; i++)
		printf("\r\n i:%d %c ", i, t[i]);

    }
#endif
}

int debug_enable(void)
{
    volatile uint32_t *shpr3 = (uint32_t *)0xE000ED20;

    printf("\r\n Enabling Debug :\n");
    if(*(unsigned int*)DHCSR & 0x1)
    {
        printf(" \r\n Halting Debug Enabled : \n");
	printf(" \r\n Cant enable monitor mode debug \n");
	return -1;

    }
    printf("\r\n DEMCR  : 0x%x \r\n", *(unsigned int *)DEMCR);
    *(unsigned int*)DEMCR = 0x00010000;
    printf("\r\n DEMCR  : 0x%x \r\n", *(unsigned int *)DEMCR);

    *shpr3 = 0xff;

    printf("Monitor Mode Debug Enabled!");

    return 0;
}

#if 0
static char buffer[100];

unsigned short hex2dec(char t)
{
	if(t >= 'a' && t <= 'f') 
	    	return ((t - 'a') + 10); 
        else if(t >= 'A' && t <= 'F')
	    return ((t - 'A') + 10);
	else
	    return t;
}

/***********************************************************************************************************
 *     The following gdb commands are supported:
 *
 * command          function                               Return value
 *
 *    g             return the value of the CPU registers  hex data or ENN
 *    G             set the value of the CPU registers     OK or ENN
 *
 *    mAA..AA,LLLL  Read LLLL bytes at address AA..AA      hex data or ENN
 *    MAA..AA,LLLL: Write LLLL bytes at address AA.AA      OK or ENN
 *
 *    c             Resume at current address              SNN   ( signal NN)
 *    cAA..AA       Continue at address AA..AA             SNN
 *
 *    s             Step one instruction                   SNN
 *    sAA..AA       Step one instruction from AA..AA       SNN
 *
 *    k             kill
 *
 *    ?             What was the last sigval ?             SNN   (signal NN)
 *
 * All commands and responses are sent with a packet which includes a
 * checksum.  A packet consists of
 *
 * $<packet info>#<checksum>.
 *
 * where
 * <packet info> :: <characters representing the command or response>
 * <checksum>    :: < two hex digits computed as modulo 256 sum of <packetinfo>>
 *
 * When a packet is received, it is first acknowledged with either '+' or '-'.
 * '+' indicates a successful transfer.  '-' indicates a failed transfer.
 *************************************************************************************************************/
char * getpacket()
{
    char ch;
    unsigned short idx = 0;
    unsigned short chksum, xmitchksum;

    char *buff = &buffer[0];

    while('$' != getCh());
retry:
    chksum = 0;
    xmitchksum = 0;
    idx = 0;

    while(1)
    {
	ch = getCh();
	if(ch == '$')
       	    goto retry;
	if(ch == '#')
	    break;
	chksum +=ch;

	buff[idx] = ch;
	printf("entered text:%c \r\n", buff[idx]);
	idx++;
    }
    buff[idx] = '\0';
    if(ch == '#')
        ch = getCh();
    else
	goto retry;

    xmitchksum = (hex2dec(ch)) << 4;
    ch = getCh();
    xmitchksum |= hex2dec(ch);

    if(xmitchksum != chksum)
    {
	    printf("checksum error :%d %d\n", xmitchksum, chksum);
	    putCh('-');
    }
    else
    {
	    printf("checksum success \n");
	    putCh('+');
    }

    return &buff[0];
}


#endif
static int prv_issue_breakpoint(void) {
  __asm("bkpt 1");
  return 0;
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

