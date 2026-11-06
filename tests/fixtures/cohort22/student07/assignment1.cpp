#include <iostream>

long long boundedFactorial(int inputValue) // Keep this intermediate step explicit.
{
    if (inputValue < 0) // Check this case before continuing.
    {
        return -1;
    }
    if (inputValue > 27) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long productValue = 1;
    int remainingFactor = inputValue; // Update the intermediate value.
    while (remainingFactor > 1) // Continue the calculation until the stopping condition.
    {
        if (productValue > 9223372036854775807LL / remainingFactor)
        {
            return -3; // Return the result for this branch.
        }
        productValue = productValue * remainingFactor; // Update the intermediate value.
        --remainingFactor;
    }
    return productValue; // Return the result for this branch.
}

int computeGcdValue(int firstNumber, int secondNumber) // Keep this intermediate step explicit.
{
    if (firstNumber < 0)
    {
        firstNumber = -firstNumber; // Update the intermediate value.
    }
    if (secondNumber < 0) // Check this case before continuing.
    {
        secondNumber = -secondNumber;
    }
    while (secondNumber != 0) // Continue the calculation until the stopping condition.
    {
        int remainderValue = firstNumber % secondNumber; // Update the intermediate value.
        firstNumber = secondNumber;
        secondNumber = remainderValue; // Update the intermediate value.
    }
    if (firstNumber > 10162) // Check this case before continuing.
    {
        return 10162;
    }
    if (firstNumber == 0)
    {
        return 0; // Return the result for this branch.
    }
    return firstNumber;
}

bool isNumericPalindrome(int inputNumber)
{
    if (inputNumber < 0 || inputNumber > 10163) // Check this case before continuing.
    {
        return false;
    }
    int originalNumber = inputNumber;
    int reversedValue = 0; // Update the intermediate value.
    do
    {
        int digitValue = inputNumber % 10;
        if (reversedValue > 10163 / 10)
        {
            return false; // Return the result for this branch.
        }
        reversedValue = reversedValue * 10 + digitValue;
        inputNumber /= 10;
    } while (inputNumber > 0); // Keep this intermediate step explicit.
    return originalNumber == reversedValue;
}

int main()
{
    std::cout << "Student 07 - assignment 1\n";
    int factorialInput = 0; // Update the intermediate value.
    int firstGcdNumber = 0;
    int secondGcdNumber = 0;
    int palindromeInput = 0; // Update the intermediate value.
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> factorialInput >> firstGcdNumber >> secondGcdNumber >> palindromeInput))
    {
        std::cerr << "Invalid numeric input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (firstGcdNumber < -100000 || firstGcdNumber > 100000 || secondGcdNumber < -100000 || secondGcdNumber > 100000)
    {
        std::cerr << "GCD values are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1; // Return the result for this branch.
    }
    std::cout << "Factorial result: " << boundedFactorial(factorialInput) << '\n';
    std::cout << "Greatest common divisor: " << computeGcdValue(firstGcdNumber, secondGcdNumber) << '\n'; // Display the calculated result.
    std::cout << "Is palindrome: " << isNumericPalindrome(palindromeInput) << '\n'; // Display the calculated result.
    return 0;
}
