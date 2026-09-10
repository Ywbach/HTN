#define RCC_APB2ENR (*(volatile unsigned int *)(0x40021018))
#define RCC_APB1ENR (*(volatile unsigned int *)(0x4002101C))

#define GPIOC_CRH   (*(volatile unsigned int *)(0x40011004))
#define GPIOC_ODR   (*(volatile unsigned int *)(0x4001100C))

#define TIM2_PSC    (*(volatile unsigned int *)(0x40000028))
#define TIM2_ARR    (*(volatile unsigned int *)(0x4000002C))
#define TIM2_SR     (*(volatile unsigned int *)(0x40000010))
#define TIM2_CR1    (*(volatile unsigned int *)(0x40000000))

#define GPIOCEN (1 << 4)
#define TIM2EN  (1 << 0)
#define PC13    (1 << 13)
#define UIF     (1 << 0)

int main(void)
{
    RCC_APB2ENR |= GPIOCEN;
    RCC_APB1ENR |= TIM2EN;

    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    TIM2_PSC = 7999;
    TIM2_ARR = 3999;
    TIM2_CR1 = 1;

    while (1)
    {
        if (TIM2_SR & UIF)
        {
            TIM2_SR &= ~UIF;
            GPIOC_ODR ^= PC13;
        }
    }
}