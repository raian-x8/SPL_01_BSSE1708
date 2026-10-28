#include <stdio.h>

int factorial(int n)
{
    int result = 1;

    for (int i = 2; i <= n; ++i)
    {
        result *= i;
    }

    return result;
}

int main(void)
{
    int number = 5;
    int answer = factorial(number);

    printf("Factorial of %d is %d\n", number, answer);

    return 0;
}