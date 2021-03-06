#ifndef UART_H_
#define UART_H_

#include "reg.h"

#define USART1_BASE      0x40013800
#define USART2_BASE      0x40004400 
#define USART3_BASE      0x40004800

#define USART_SR_OFFSET   0x00 /* Status register    */
#define USART_DR_OFFSET   0x04 /* Data register      */ 
#define USART_BRR_OFFSET  0x08 /* Baud rate register */
#define USART_CR1_OFFSET  0x0C /* Control register 1 */
#define USART_CR2_OFFSET  0x10 /* Control register 2 */
#define USART_CR3_OFFSET  0x14 /* Control register 3 */
#define USART_GTPR_OFFSET 0x18 /* Guard time and prescaler register */

#define USART1_SR (USART1_BASE + USART_SR_OFFSET)
#define USART2_SR (USART2_BASE + USART_SR_OFFSET)
#define USART3_SR (USART3_BASE + USART_SR_OFFSET)

#define USART1_DR (USART1_BASE + USART_DR_OFFSET)
#define USART2_DR (USART2_BASE + USART_DR_OFFSET)
#define USART3_DR (USART3_BASE + USART_DR_OFFSET)

#define USART1_BRR (USART1_BASE + USART_BRR_OFFSET)
#define USART2_BRR (USART2_BASE + USART_BRR_OFFSET)
#define USART3_BRR (USART3_BASE + USART_BRR_OFFSET)

#define USART1_CR1 (USART1_BASE + USART_CR1_OFFSET)
#define USART2_CR1 (USART2_BASE + USART_CR1_OFFSET)
#define USART3_CR1 (USART3_BASE + USART_CR1_OFFSET)

#define USART1_CR2 (USART1_BASE + USART_CR2_OFFSET)
#define USART2_CR2 (USART2_BASE + USART_CR2_OFFSET)
#define USART3_CR2 (USART3_BASE + USART_CR2_OFFSET)

#define USART1_CR3 (USART1_BASE + USART_CR3_OFFSET)
#define USART2_CR3 (USART2_BASE + USART_CR3_OFFSET)
#define USART3_CR3 (USART3_BASE + USART_CR3_OFFSET)

#define USART1_GTPR (USART1_BASE + USART_GTPR_OFFSET)
#define USART2_GTPR (USART2_BASE + USART_GTPR_OFFSET)
#define USART3_GTPR (USART3_BASE + USART_GTPR_OFFSET)

void uart_init(void);

void uart_tx(char *t);

#endif
