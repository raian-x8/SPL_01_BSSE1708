#include <stdio.h>

int main(void)
{
    int first = 0;
    int second = 1;

    // Print the first ten Fibonacci terms
    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", first);

        int next = first + second;
        first = second;
        second = next;
    }

    return 0;
}