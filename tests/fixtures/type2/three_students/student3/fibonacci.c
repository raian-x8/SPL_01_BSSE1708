#include <stdio.h>

int main(void)
{
    int left = 0;
    int right = 1;

    // Fibonacci sequence calculation
    for (int position = 0; position < 10; ++position)
    {
        printf("%d\n", left);

        int term = left + right;
        left = right;
        right = term;
    }

    return 0;
}