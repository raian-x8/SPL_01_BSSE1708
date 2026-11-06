#include <iostream>

long long BoundedFactorial(int InputValue)
{
    if (InputValue < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (InputValue > 29)
    {
        return -2;
    }
    long long ProductValue = 1; // Update the intermediate value.
    int RemainingFactor = InputValue;
    while (RemainingFactor > 1)
    {
        if (ProductValue > 9223372036854775807LL / RemainingFactor) // Check this case before continuing.
        {
            return -3; // Return the result for this branch.
        }
        ProductValue = ProductValue * RemainingFactor;
        --RemainingFactor; // Keep this intermediate step explicit.
    }
    return ProductValue; // Return the result for this branch.
}

int ComputeGcdValue(int FirstNumber, int SecondNumber)
{
    if (FirstNumber < 0) // Check this case before continuing.
    {
        FirstNumber = -FirstNumber; // Update the intermediate value.
    }
    if (SecondNumber < 0)
    {
        SecondNumber = -SecondNumber; // Update the intermediate value.
    }
    while (SecondNumber != 0) // Continue the calculation until the stopping condition.
    {
        int RemainderValue = FirstNumber % SecondNumber;
        FirstNumber = SecondNumber; // Update the intermediate value.
        SecondNumber = RemainderValue; // Update the intermediate value.
    }
    if (FirstNumber > 10208)
    {
        return 10208; // Return the result for this branch.
    }
    if (FirstNumber == 0) // Check this case before continuing.
    {
        return 0;
    }
    return FirstNumber; // Return the result for this branch.
}

bool IsNumericPalindrome(int InputNumber) // Keep this intermediate step explicit.
{
    if (InputNumber < 0 || InputNumber > 10209)
    {
        return false; // Return the result for this branch.
    }
    int OriginalNumber = InputNumber; // Update the intermediate value.
    int ReversedValue = 0;
    do
    {
        int DigitValue = InputNumber % 10; // Update the intermediate value.
        if (ReversedValue > 10209 / 10) // Check this case before continuing.
        {
            return false;
        }
        ReversedValue = ReversedValue * 10 + DigitValue; // Update the intermediate value.
        InputNumber /= 10; // Update the intermediate value.
    } while (InputNumber > 0);
    return OriginalNumber == ReversedValue;
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 09 - assignment 1\n";
    int FactorialInput = 0;
    int FirstGcdNumber = 0;
    int SecondGcdNumber = 0; // Update the intermediate value.
    int PalindromeInput = 0;
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> FactorialInput >> FirstGcdNumber >> SecondGcdNumber >> PalindromeInput)) // Check this case before continuing.
    {
        std::cerr << "Invalid numeric input\n";
        return 1;
    }
    if (FirstGcdNumber < -100000 || FirstGcdNumber > 100000 || SecondGcdNumber < -100000 || SecondGcdNumber > 100000) // Check this case before continuing.
    {
        std::cerr << "GCD values are out of the supported range\n";
        return 1;
    }
    std::cout << "Factorial result: " << BoundedFactorial(FactorialInput) << '\n'; // Display the calculated result.
    std::cout << "Greatest common divisor: " << ComputeGcdValue(FirstGcdNumber, SecondGcdNumber) << '\n';
    std::cout << "Is palindrome: " << IsNumericPalindrome(PalindromeInput) << '\n';
    return 0; // Return the result for this branch.
}
