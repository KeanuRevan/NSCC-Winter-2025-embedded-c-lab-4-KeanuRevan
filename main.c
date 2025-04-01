#include <stdint.h>
#include <stdio.h>

extern void _print_ch(const char *);

void print_ch(char ch) {
    _print_ch(&ch);
}

#define GPIOA_BASE = 0x50000000
#define GPIOA_MODER  ((volatile uint32_t *)0x50000000)
// #define GPIOA_MODER  (unsigned long *)0x50000000)


int main() {

    *GPIOA_MODER &= ~0x00000800UL;

    while(1) {
        /* empty */
        print_ch('X');
    }
    return 0;
}