#include <stdio.h>

extern void _print_ch(const char *);

void print_ch(char ch) {
    _print_ch(&ch);
}

int main() {
    while(1) {
        /* empty */
        print_ch('X');
    }
    return 0;
}