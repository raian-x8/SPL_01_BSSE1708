#include <stdio.h>

int main(void)
{
    int number = 17;
    int isPrime = 1;

    if (number < 2)
    {
        isPrime = 0;
    }

    for (int divisor = 2; divisor * divisor <= number; ++divisor)
    {
        if (number % divisor == 0)
        {
            isPrime = 0;
            break;
        }
    }

    printf("Prime status: %d\n", isPrime);

    return 0;
}