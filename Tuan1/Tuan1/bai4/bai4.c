#define RCC_APB2ENR (*(volatile unsigned int *)0x40021018)

#define GPIOA_CRL   (*(volatile unsigned int *)0x40010800)
#define GPIOA_IDR   (*(volatile unsigned int *)0x40010808)
#define GPIOA_ODR   (*(volatile unsigned int *)0x4001080C)

#define GPIOC_CRH   (*(volatile unsigned int *)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int *)0x4001100C)

void delay(volatile unsigned int time)
{
    while (time--)
    {
        __asm volatile ("nop");
    }
}

int main(void)
{
    unsigned int led_state = 0;

    RCC_APB2ENR |= (1 << 2);
    RCC_APB2ENR |= (1 << 4);

    GPIOA_CRL &= ~(0xF << 24);
    GPIOA_CRL |= (0x8 << 24);

    GPIOA_ODR |= (1 << 6);

    GPIOC_CRH &= ~(0xF << 28);
    GPIOC_CRH |= (0x2 << 28);

    GPIOC_ODR &= ~(1 << 15);

    while (1)
    {
        if ((GPIOA_IDR & (1 << 6)) == 0)
        {
            delay(20000);

            if ((GPIOA_IDR & (1 << 6)) == 0)
            {
                while ((GPIOA_IDR & (1 << 6)) == 0);

                delay(20000);

                led_state = !led_state;

                if (led_state)
                    GPIOC_ODR |= (1 << 15);
                else
                    GPIOC_ODR &= ~(1 << 15);
            }
        }
    }
}