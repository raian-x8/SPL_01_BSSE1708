#include <stdio.h>

int factorial(int value)
{
    int product = 1;

    for (int step = 2; step <= value; ++step)
    {
        product *= step;
    }

    return product;
}

int main(void)
{
    int input = 5;
    int output = factorial(input);

    printf("Factorial of %d is %d\n", input, output);

    return 0;
}