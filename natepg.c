#include <stdio.h>

int main(void)
{
    int x = 0b0001011;
    printf("antes %b\n", x);

    // int mask = 0b10000000;
    // int meupau = x & mask;
    // // printf("depois %b\n", meupau);
    int i = 0;
    while (i < 9)
    {
        printf("%b", (x & 0b00000001));
        x >>= 1;
        i++;
    }

    return 0;
}
