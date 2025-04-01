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

int main() {

    *RCC_IOPENR = 0x00000001UL;  // Enable GPIOA clock

    // // Set PA5 as output
    *GPIOA_MODER &= ~0x00000800UL;

    while (1) {
        if (*GPIOA_ODR & 0x00000020UL) {
            *GPIOA_ODR &= ~0x00000020UL;  // Turn LED off
        } else {
            *GPIOA_ODR |= 0x00000020UL;   // Turn LED on
        }
        print_ch('Y');
    }
    return 0;
}
