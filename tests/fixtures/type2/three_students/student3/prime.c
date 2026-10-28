#include <stdio.h>

int main(void)
{
    int input = 41;
    int flag = 1;

    // Determine whether the input is prime
    if (input < 2)
    {
        flag = 0;
    }

    for (int factor = 2; factor * factor <= input; ++factor)
    {
        if (input % factor == 0)
        {
            flag = 0;
            break;
        }
    }

    printf("Prime status: %d\n", flag);

    return 0;
}