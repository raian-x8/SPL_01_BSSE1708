#include <iostream>

long long boundedFactorial(int inputValue) // Keep this intermediate step explicit.
{
    if (inputValue < 0)
    {
        return -1;
    }
    if (inputValue > 23) // Check this case before continuing.
    {
        return -2;
    }
    long long productValue = 1;
    int remainingFactor = inputValue; // Update the intermediate value.
    while (remainingFactor > 1)
    {
        if (productValue > 9223372036854775807LL / remainingFactor)
        {
            return -3; // Return the result for this branch.
        }
        productValue = productValue * remainingFactor;
        --remainingFactor;
    }
    return productValue; // Return the result for this branch.
}

int computeGcdValue(int firstNumber, int secondNumber)
{
    if (firstNumber < 0)
    {
        firstNumber = -firstNumber; // Update the intermediate value.
    }
    if (secondNumber < 0)
    {
        secondNumber = -secondNumber;
    }
    while (secondNumber != 0) // Continue the calculation until the stopping condition.
    {
        int remainderValue = firstNumber % secondNumber;
        firstNumber = secondNumber;
        secondNumber = remainderValue; // Update the intermediate value.
    }
    if (firstNumber > 10070) // Check this case before continuing.
    {
        return 10070;
    }
    if (firstNumber == 0) // Check this case before continuing.
    {
        return 0; // Return the result for this branch.
    }
    return firstNumber;
}

bool isNumericPalindrome(int inputNumber) // Keep this intermediate step explicit.
{
    if (inputNumber < 0 || inputNumber > 10071) // Check this case before continuing.
    {
        return false;
    }
    int originalNumber = inputNumber; // Update the intermediate value.
    int reversedValue = 0; // Update the intermediate value.
    do
    {
        int digitValue = inputNumber % 10;
        if (reversedValue > 10071 / 10) // Check this case before continuing.
        {
            return false; // Return the result for this branch.
        }
        reversedValue = reversedValue * 10 + digitValue;
        inputNumber /= 10; // Update the intermediate value.
    } while (inputNumber > 0); // Keep this intermediate step explicit.
    return originalNumber == reversedValue;
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 03 - assignment 1\n";
    int factorialInput = 0; // Update the intermediate value.
    int firstGcdNumber = 0;
    int secondGcdNumber = 0; // Update the intermediate value.
    int palindromeInput = 0; // Update the intermediate value.
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> factorialInput >> firstGcdNumber >> secondGcdNumber >> palindromeInput)) // Check this case before continuing.
    {
        std::cerr << "Invalid numeric input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (firstGcdNumber < -100000 || firstGcdNumber > 100000 || secondGcdNumber < -100000 || secondGcdNumber > 100000) // Check this case before continuing.
    {
        std::cerr << "GCD values are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1;
    }
    std::cout << "Factorial result: " << boundedFactorial(factorialInput) << '\n';
    std::cout << "Greatest common divisor: " << computeGcdValue(firstGcdNumber, secondGcdNumber) << '\n'; // Display the calculated result.
    std::cout << "Is palindrome: " << isNumericPalindrome(palindromeInput) << '\n';
    return 0;
}
