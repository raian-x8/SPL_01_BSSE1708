#include <stdio.h>

int main(void)
{
    int value = 2;

    /* Display even integers up to ten */
    while (value <= 10)
    {
        printf("%d\n", value);
        value += 2;
    }

    return 0;
}