#include <stdio.h>

int main(void)
{
    int value = 41;
    int isPrime = 1;

    /* Check divisibility */
    if (value < 2)
    {
        isPrime = 0;
    }

    for (int candidate = 2; candidate * candidate <= value; ++candidate)
    {
        if (value % candidate == 0)
        {
            isPrime = 0;
            break;
        }
    }

    printf("Prime status: %d\n", isPrime);

    return 0;
}