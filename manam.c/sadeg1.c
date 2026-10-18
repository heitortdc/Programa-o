#include <stdio.h>
int main() {
    char c1 = getchar();
    getchar(); // consome o '\n'
    char c2 = getchar();
    putchar(c1);
    putchar(c2);
    return 0;
}