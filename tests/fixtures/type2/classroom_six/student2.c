#include <stdio.h>

int main(void)
{
    int even = 2;

    // Print only even numbers
    while (even <= 10)
    {
        printf("%d\n", even);
        even += 2;
    }

    return 0;
}