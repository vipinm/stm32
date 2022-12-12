
#include<stdio.h>
#include<stdint.h>
#include "reg.h"
#include <debug.h>

/* stm32f103c8t6 sram:20kb flash:64kb */
#define SRAM_START  0x20000000U
#define SRAM_SIZE   (20U * 1024U) //20KB
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))

#define STACK_START   SRAM_END

typedef struct __attribute__((packed)) ContextStateFrame {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8;
  uint32_t r9;
  uint32_t r10;
  uint32_t r11;
  uint32_t r12;
  uint32_t r13;
  uint32_t lr;
  uint32_t pc;
  uint32_t xpsr;
} sContextStateFrame;

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

int main(void);
void __libc_init_array(void);

void Reset_Handler(void);
void DebugMon_Handler(void);

void NMI_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
//void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void TAMP_STAMP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));      
void RTC_WKUP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));                               
void FLASH_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void RCC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void EXTI0_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI1_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void DMA1_Channel0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Channel7_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void ADC1_2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));             
void USB_HP_CAN_TX_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void USB_HP_CAN_RX_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN1_RX1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN1_SCE_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI9_5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM1_BRK_TIM9_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_UP_TIM10_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_TRG_COM_TIM11_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM3_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM4_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void I2C1_EV_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C1_ER_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_EV_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_ER_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void SPI1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));           
void SPI2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void USART1_IRQHandler  		(void) __attribute__ ((weak, alias("Default_Handler")));         
void USART2_IRQHandler  		(void) __attribute__ ((weak, alias("Default_Handler")));        
void USART3_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));     
void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));    
void USBWakeup_IRQHandler        	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_BRK_TIM12_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void FSMC_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel0_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void ETH_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));
void ETH_WKUP_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DCMI_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void CRYP_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void HASH_RNG_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));                          


uint32_t vectors[] __attribute__((section(".isr_vector")))   = {
	STACK_START,
	(uint32_t)Reset_Handler,
	(uint32_t)NMI_Handler,
	(uint32_t)HardFault_Handler,
	(uint32_t)MemManage_Handler,
	(uint32_t)BusFault_Handler,
	(uint32_t)UsageFault_Handler,
	0,
	0,
	0,
	0,
	(uint32_t)SVC_Handler,
	(uint32_t)DebugMon_Handler,
	0,
	(uint32_t)PendSV_Handler,
	(uint32_t)SysTick_Handler,
	(uint32_t)WWDG_IRQHandler,
	(uint32_t)PVD_IRQHandler,         
	(uint32_t)TAMP_STAMP_IRQHandler,  
	(uint32_t)RTC_WKUP_IRQHandler,    
	(uint32_t)FLASH_IRQHandler,                      
	(uint32_t)RCC_IRQHandler,         
	(uint32_t)EXTI0_IRQHandler,       
	(uint32_t)EXTI1_IRQHandler,       
	(uint32_t)EXTI2_IRQHandler,       
	(uint32_t)EXTI3_IRQHandler,       
	(uint32_t)EXTI4_IRQHandler,       
	(uint32_t)DMA1_Channel0_IRQHandler,
	(uint32_t)DMA1_Channel1_IRQHandler,
	(uint32_t)DMA1_Channel2_IRQHandler,
	(uint32_t)DMA1_Channel3_IRQHandler,
	(uint32_t)DMA1_Channel4_IRQHandler,
	(uint32_t)DMA1_Channel5_IRQHandler,
	(uint32_t)DMA1_Channel6_IRQHandler,
	(uint32_t)DMA1_Channel7_IRQHandler,
	(uint32_t)ADC1_2_IRQHandler,         
	(uint32_t)USB_HP_CAN_TX_IRQHandler,     
	(uint32_t)USB_HP_CAN_RX_IRQHandler,    
	(uint32_t)CAN1_RX1_IRQHandler,    
	(uint32_t)CAN1_SCE_IRQHandler,    
	(uint32_t)EXTI9_5_IRQHandler,     
	(uint32_t)TIM1_BRK_TIM9_IRQHandler,
	(uint32_t)TIM1_UP_TIM10_IRQHandler,
	(uint32_t)TIM1_TRG_COM_TIM11_IRQHandler,
	(uint32_t)TIM1_CC_IRQHandler,     
	(uint32_t)TIM2_IRQHandler,        
	(uint32_t)TIM3_IRQHandler,        
	(uint32_t)TIM4_IRQHandler,        
	(uint32_t)I2C1_EV_IRQHandler,     
	(uint32_t)I2C1_ER_IRQHandler,     
	(uint32_t)I2C2_EV_IRQHandler,     
	(uint32_t)I2C2_ER_IRQHandler,     
	(uint32_t)SPI1_IRQHandler,        
	(uint32_t)SPI2_IRQHandler,        
	(uint32_t)USART1_IRQHandler,      
	(uint32_t)USART2_IRQHandler,      
	(uint32_t)USART3_IRQHandler,      
	(uint32_t)EXTI15_10_IRQHandler,   
	(uint32_t)RTC_Alarm_IRQHandler,   
	(uint32_t)USBWakeup_IRQHandler, 
	(uint32_t)TIM8_BRK_TIM12_IRQHandler,
	(uint32_t)TIM8_UP_TIM13_IRQHandler,
	(uint32_t)TIM8_TRG_COM_TIM14_IRQHandler,
	(uint32_t)TIM8_CC_IRQHandler,     
	(uint32_t)ADC3_IRQHandler,     
	(uint32_t)FSMC_IRQHandler,        
	(uint32_t)SDIO_IRQHandler,        
	(uint32_t)TIM5_IRQHandler,        
	(uint32_t)SPI3_IRQHandler,        
	(uint32_t)UART4_IRQHandler,       
	(uint32_t)UART5_IRQHandler,       
	(uint32_t)TIM6_DAC_IRQHandler,    
	(uint32_t)TIM7_IRQHandler,        
	(uint32_t)DMA2_Channel1_IRQHandler,
	(uint32_t)DMA2_Channel2_IRQHandler,
	(uint32_t)DMA2_Channel3_IRQHandler,
	(uint32_t)DMA2_Channel4_5_IRQHandler,
};


void Default_Handler(void)
{
	while(1);
}

void Reset_Handler(void)
{
	//copy .data section to SRAM
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	
	uint8_t *pDst = (uint8_t*)&_sdata; //sram
	uint8_t *pSrc = (uint8_t*)&_la_data; //flash
	
	for(uint32_t i =0 ; i < size ; i++)
	{
		*pDst++ = *pSrc++;
	}
	
	//Init. the .bss section to zero in SRAM
	size = (uint32_t)&__bss_end__ - (uint32_t)&__bss_start__;
	pDst = (uint8_t*)&__bss_start__;
	for(uint32_t i =0 ; i < size ; i++)
	{
		*pDst++ = 0;
	}
        __libc_init_array();
        main();
}


#define BUFMAX 2048
static const char hexchars[]="0123456789abcdef";
static unsigned char remcomOutBuffer[BUFMAX];
static char remcomInBuffer[BUFMAX];

enum regnames {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, LR, PC, XPSR};

static unsigned char *
mem2hex (unsigned char *mem, unsigned char *buf, int count)
{
  unsigned char ch;

  while (count-- > 0)
    {
      ch = *mem++;
      *buf++ = hexchars[ch >> 4];
      *buf++ = hexchars[ch & 0xf];
    }

  *buf = 0;

  return buf;
}
void handlem(char *ptr, unsigned int *val, unsigned int *len)
{
	char *ch = ptr;
	unsigned int idx = 0, num =0 , addr = 0, i;

	while(*ch++ != ',')
	{
               idx++;
	}
	*len = *ch - '0';

	for(i = 0; i < idx; i++)
	{
           if((ptr[i] >= 'a') && (ptr[i] <= 'f'))
               num = 10 + ptr[i] - 'a' ;
	   else if((ptr[i] >= '0') && (ptr[i] <= '9'))
	       num = ptr[i] - '0';
           addr |= num << (((idx-1)- i)*4); 
	}
	return addr;

}
unsigned int test = 0xff345;

static int
hex (unsigned char ch)
{
  if (ch >= 'a' && ch <= 'f')
    return ch-'a'+10;
  if (ch >= '0' && ch <= '9')
    return ch-'0';
  if (ch >= 'A' && ch <= 'F')
    return ch-'A'+10;
  return -1;
}


static int
hexToInt(char **ptr, int *intValue)
{
  int numChars = 0;
  int hexValue;

  *intValue = 0;

  while (**ptr)
    {
      hexValue = hex(**ptr);
      if (hexValue < 0)
        break;

      *intValue = (*intValue << 4) | hexValue;
      numChars ++;

      (*ptr)++;
    }

  return (numChars);
}


void debug_monitor_handler_c(sContextStateFrame *frame) 
{
    const uint32_t dfsr_dwt_evt_bitmask = (1 << 2);
    const uint32_t dfsr_bkpt_evt_bitmask = (1 << 1);
    const uint32_t dfsr_halt_evt_bitmask = (1 << 0);

    uint32_t is_dwt_dbg_evt =  (*(unsigned int *)DFSR & dfsr_dwt_evt_bitmask) ? 1:0;
    uint32_t is_bkpt_dbg_evt = (*(unsigned int *)DFSR & dfsr_bkpt_evt_bitmask) ? 1: 0;
    uint32_t is_halt_dbg_evt = (*(unsigned int *)DFSR & dfsr_halt_evt_bitmask) ? 1:0;
    char *ptr;

    printf("\r\nDebugMonitor Exception\n");
    printf("DEMCR: 0x%08x", *(unsigned int *)DEMCR);
    printf("DFSR:  0x%08x (bkpt=%d, halt=%d, dwt=%d)", *(unsigned int *)DFSR,
              (int)is_bkpt_dbg_evt, (int)is_halt_dbg_evt,
              (int)is_dwt_dbg_evt);

    printf("\r\n Register Dump");
    printf("\r\n r0  =0x%08x", frame->r0);
    printf("\r\n r1  =0x%08x", frame->r1);
    printf("\r\n r2  =0x%08x", frame->r2);
    printf("\r\n r3  =0x%08x", frame->r3);
    printf("\r\n r4  =0x%08x", frame->r4);
    printf("\r\n r5  =0x%08x", frame->r5);
    printf("\r\n r6  =0x%08x", frame->r6);
    printf("\r\n r7  =0x%08x", frame->r7);
    printf("\r\n r8  =0x%08x", frame->r8);
    printf("\r\n r9  =0x%08x", frame->r9);
    printf("\r\n r10  =0x%08x", frame->r10);
    printf("\r\n r11  =0x%08x", frame->r11);
    printf("\r\n r12  =0x%08x", frame->r12);
    printf("\r\n r13 =0x%08x", frame->r13);
    printf("\r\n lr  =0x%08x", frame->lr);
    printf("\r\n pc  =0x%08x", frame->pc);
    printf("\r\n xpsr=0x%08x", frame->xpsr);
   

    remcomOutBuffer[0] = 'S';
    remcomOutBuffer[1] = '0';
    remcomOutBuffer[2] = '5';
    remcomOutBuffer[3]= 0;
    putpacket(remcomOutBuffer);
    while(1)
    {
        const uint16_t instruction = *(uint16_t*)frame->pc;
	unsigned int addr = 0, length =0;
	remcomOutBuffer[0] = 0;
        if(is_bkpt_dbg_evt)
        {
	    ptr = getpacket();
	    switch(*ptr++)
	    {
                case '?':
	            remcomOutBuffer[0] = 'S';
	            remcomOutBuffer[1] = '0';
	            remcomOutBuffer[2] = '5';
	            remcomOutBuffer[3] = 0;
		    break;
		case 'g':
                    mem2hex((unsigned char *)frame, remcomOutBuffer, 64);
		    break;
		case 'm':
                    if (hexToInt(&ptr, &addr)
                         && *ptr++ == ','
                         && hexToInt(&ptr, &length))
                    {
                        if (mem2hex((char *)addr, remcomOutBuffer, length))
                            break;
                        strcpy (remcomOutBuffer, "E03");
                    }
                    else
                        strcpy(remcomOutBuffer,"E01");
		    /*handlem(++ptr, &val, &len);
		    mem2hex((unsigned char *)val, remcomOutBuffer, len);*/
		    break;
		default:
		    break;
	    }
	    putpacket(remcomOutBuffer);
            if ((instruction & 0xff00) == 0xbe00) 
	    {
              // advance past breakpoint instruction
                frame->pc += sizeof(instruction);
            } 
           *(unsigned int*)DFSR = dfsr_bkpt_evt_bitmask;
          /**(unsigned int*)DEMCR |=(1 << 18);*/
        }
	else if(is_halt_dbg_evt)
        {
          *(unsigned int*)DFSR = dfsr_halt_evt_bitmask;

          *(unsigned int*)DEMCR &=~(1 << 18);
        }
    }
}

__attribute__((naked))
void DebugMon_Handler(void) {
  __asm volatile(
      "tst lr, #4 \n"
      "ite eq \n"
      "mrseq r0, msp \n"
      "mrsne r0, psp \n"
      "b debug_monitor_handler_c \n");
}







