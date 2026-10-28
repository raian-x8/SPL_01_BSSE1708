#include <stdio.h>

int main(void)
{
    int number = 41;
    int prime = 1;

    // Handle numbers smaller than two
    if (number < 2)
    {
        prime = 0;
    }

    for (int divisor = 2; divisor * divisor <= number; ++divisor)
    {
        if (number % divisor == 0)
        {
            prime = 0;
            break;
        }
    }

    printf("Prime status: %d\n", prime);

    return 0;
}