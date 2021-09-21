#include<stdint.h>

#define RCC_BASE            0x40021000U

#define GPIOA_BASE          0x40010800U
#define GPIOB_BASE          0x40010C00U
#define GPIOC_BASE          0x40011000U
#define GPIOD_BASE          0x40011400U
#define GPIOE_BASE          0x40011800U
#define NVIC_BASE           0xE000E100U
#define AFIO_BASE           0x40010000U

#define RCC_CR_OFFSET       0x00U   // Control register for clock and reset control
#define RCC_CFGR_OFFSET     0x04U   // Configuration register for clock and reset control
#define RCC_APB2ENR_OFFSET  0x18U   // Offset address for advanced peripheral bus

#define GPIOx_CRL           0x00U   // GPIO control registers for LOW register address 0-7
#define GPIOx_CRH           0x04U   // GPIO control registers for HIGH register address 8-15
#define GPIOx_IDR           0X08U   // GPIO input data register address
#define GPIOx_ODR           0X0CU   // GPIO output data register address
#define GPIOx_BSRR          0x10U   // GPIO bit SET/RESET registers register address
#define GPIOx_BRR           0x14U   // GPIO bit reset register

#define NVIC_USART1_OFFSET  0x004U

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

#define RCC_CR          (RCC_BASE + RCC_CR_OFFSET)
#define RCC_CFGR        (RCC_BASE + RCC_CFGR_OFFSET)
#define RCC_APB2ENR     (RCC_BASE + RCC_APB2ENR_OFFSET)

#define GPIOA_MODERL    (GPIOA_BASE + GPIOx_CRL)
#define GPIOA_MODERH    (GPIOA_BASE + GPIOx_CRH)
#define GPIOA_ODR       (GPIOA_BASE + GPIOx_ODR)
#define GPIOA_BSRR      (GPIOA_BASE + GPIOx_BSRR)
#define GPIOA_BRR       (GPIOA_BASE + GPIOx_BRR)

#define GPIOB_MODERL    (GPIOB_BASE + GPIOx_CRL)
#define GPIOB_MODERH    (GPIOB_BASE + GPIOx_CRH)
#define GPIOB_ODR       (GPIOB_BASE + GPIOx_ODR)
#define GPIOB_BSRR      (GPIOB_BASE + GPIOx_BSRR)
#define GPIOB_BRR       (GPIOB_BASE + GPIOx_BRR)

#define GPIOC_MODERL    (GPIOC_BASE + GPIOx_CRL)
#define GPIOC_MODERH    (GPIOC_BASE + GPIOx_CRH)
#define GPIOC_ODR       (GPIOC_BASE + GPIOx_ODR)
#define GPIOC_BSRR      (GPIOC_BASE + GPIOx_BSRR)
#define GPIOC_BRR       (GPIOC_BASE + GPIOx_BRR)

#define NVIC_USART1     (NVIC_BASE + NVIC_USART1_OFFSET)

#define FLASH_ACR       0x40022000

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

#define REG(x) (*(unsigned int *)x)

#define REG_GET(x) (x)
#define REG_SET(x, data) x = data

typedef struct {
    uint32_t rcc_cr;
    uint32_t rcc_cfgr;
    uint32_t rcc_cir;
    uint32_t rcc_apb2rstr;
    uint32_t rcc_apb1rstr;
    uint32_t rcc_ahbenr;
    uint32_t rcc_apb2enr;
    uint32_t rcc_apb1enr;
    uint32_t rcc_bdcr;
    uint32_t rcc_csr;
}rcc;

#define RCC ((rcc *)(RCC_BASE))

typedef struct{
    uint32_t gpio_crl;
    uint32_t gpio_crh;
    uint32_t gpio_idr;
    uint32_t gpio_odr;
    uint32_t gpio_bsrr;
    uint32_t gpio_brr;
    uint32_t gpio_lckr;
}gpio;

#define GPIOA ((gpio *)(GPIOA_BASE))
#define GPIOB ((gpio *)(GPIOB_BASE))
#define GPIOC ((gpio *)(GPIOC_BASE))
typedef struct{
    uint32_t afio_evcr;
    uint32_t afio_mapr;
    uint32_t afio_exticr1;
    uint32_t afio_exticr2;
    uint32_t afio_exticr3;
    uint32_t afio_exticr4;
    uint32_t afio_mapr2;
}afio;
#define AFIO ((afio *)(AFIO_BASE))


typedef struct{
    uint32_t usart_sr;
    uint32_t usart_dr;
    uint32_t usart_brr;
    uint32_t usart_cr1;
    uint32_t usart_cr2;
    uint32_t usart_cr3;
    uint32_t usart_gtpr;
}usart;
#define USART1 ((usart *)(USART1_BASE))
#define USART2 ((usart *)(USART2_BASE))
#define USART3 ((usart *)(USART3_BASE))
