#define RCC_APB2ENR (*(volatile unsigned int *)0x40021018)

#define GPIOA_CRL   (*(volatile unsigned int *)0x40010800)
#define GPIOA_CRH   (*(volatile unsigned int *)0x40010804)
#define GPIOA_IDR   (*(volatile unsigned int *)0x40010808)
#define GPIOA_ODR   (*(volatile unsigned int *)0x4001080C)

void delay(unsigned int time)
{
    volatile unsigned int i;

    for (i = 0; i < time; i++)
        __asm volatile ("nop");
}

int main(void)
{
    unsigned int i;
    unsigned int led = 0;

    RCC_APB2ENR |= (1 << 2);

    GPIOA_CRL = 0x88888888;
    GPIOA_CRH = 0x22222222;

    GPIOA_ODR = 0x00FF;

    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            if (!(GPIOA_IDR & (1 << i)))
            {
                delay(10000);

                if (!(GPIOA_IDR & (1 << i)))
                {
                    led ^= (1 << i);

                    while (!(GPIOA_IDR & (1 << i)));

                    delay(10000);
                }
            }
        }

        GPIOA_ODR = 0x00FF | (led << 8);
    }
}