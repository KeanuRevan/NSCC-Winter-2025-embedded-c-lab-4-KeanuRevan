#include <stdint.h>
#include <stdio.h>

extern void _print_ch(const char *);

void print_ch(char ch) {
    _print_ch(&ch);
}

#define RCC_BASE 0x40021000
#define RCC_IOPENR (unsigned long *)0x40021034

#define GPIOA_BASE 0x50000000
#define GPIOA_MODER  (unsigned long *)0x50000000
#define GPIOA_ODR (unsigned long *)0x50000014

#define GPIOC_BASE 0x50000800
#define GPIOC_MODER  (unsigned long *)0x50000800
#define GPIOC_IDR (unsigned long *)0x50000810

int main() {

    *RCC_IOPENR |= 0x00000005UL;    // Enable GPIOA and GPIOC register clock

    // // Set PA5 as output
    *GPIOA_MODER &= ~0x00000800UL;

    //set PC13 as a digital input
    *GPIOC_MODER &= ~0x0C000000UL;

    bool pressed = false;

    while (1) {

        if (*GPIOC_IDR & 0x00002000UL) {
            *GPIOA_ODR &= ~0x00000020UL;  // Turn LED off
            if (pressed == false) {
                pressed = true;
                print_ch('N');
            }

        } else {
            *GPIOA_ODR |= 0x00000020UL;   // Turn LED on
            if (pressed == true) {
                pressed = false;
                print_ch('Y');
            }
        }
    }
    return 0;
}