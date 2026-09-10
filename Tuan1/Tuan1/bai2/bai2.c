#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080C)

void delay(uint32_t time)
{
    volatile uint32_t i;

    for (i = 0; i < time; i++)
    {
        __asm volatile ("nop");
    }
}

int main(void)
{
    uint8_t i;

    RCC_APB2ENR |= (1 << 2);

    GPIOA_CRL = 0x22222222;

    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            GPIOA_ODR = (1 << i);
            delay(100000);
        }

        for (i = 6; i > 0; i--)
        {
            GPIOA_ODR = (1 << i);
            delay(100000);
        }
    }
}