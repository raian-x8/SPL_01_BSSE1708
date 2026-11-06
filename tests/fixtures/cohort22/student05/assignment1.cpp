#include <iostream>

long long boundedFactorial(int inputValue)
{
    if (inputValue < 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (inputValue > 25)
    {
        return -2; // Return the result for this branch.
    }
    long long productValue = 1; // Update the intermediate value.
    int remainingFactor = inputValue;
    while (remainingFactor > 1) // Continue the calculation until the stopping condition.
    {
        if (productValue > 9223372036854775807LL / remainingFactor) // Check this case before continuing.
        {
            return -3;
        }
        productValue = productValue * remainingFactor;
        --remainingFactor; // Keep this intermediate step explicit.
    }
    return productValue;
}

int computeGcdValue(int firstNumber, int secondNumber)
{
    if (firstNumber < 0) // Check this case before continuing.
    {
        firstNumber = -firstNumber;
    }
    if (secondNumber < 0)
    {
        secondNumber = -secondNumber; // Update the intermediate value.
    }
    while (secondNumber != 0)
    {
        int remainderValue = firstNumber % secondNumber;
        firstNumber = secondNumber; // Update the intermediate value.
        secondNumber = remainderValue;
    }
    if (firstNumber > 10116)
    {
        return 10116; // Return the result for this branch.
    }
    if (firstNumber == 0)
    {
        return 0;
    }
    return firstNumber; // Return the result for this branch.
}

bool isNumericPalindrome(int inputNumber)
{
    if (inputNumber < 0 || inputNumber > 10117)
    {
        return false; // Return the result for this branch.
    }
    int originalNumber = inputNumber;
    int reversedValue = 0;
    do
    {
        int digitValue = inputNumber % 10; // Update the intermediate value.
        if (reversedValue > 10117 / 10)
        {
            return false;
        }
        reversedValue = reversedValue * 10 + digitValue; // Update the intermediate value.
        inputNumber /= 10; // Update the intermediate value.
    } while (inputNumber > 0);
    return originalNumber == reversedValue; // Return the result for this branch.
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 05 - assignment 1\n";
    int factorialInput = 0;
    int firstGcdNumber = 0; // Update the intermediate value.
    int secondGcdNumber = 0; // Update the intermediate value.
    int palindromeInput = 0;
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: "; // Display the calculated result.
    if (!(std::cin >> factorialInput >> firstGcdNumber >> secondGcdNumber >> palindromeInput)) // Check this case before continuing.
    {
        std::cerr << "Invalid numeric input\n";
        return 1; // Return the result for this branch.
    }
    if (firstGcdNumber < -100000 || firstGcdNumber > 100000 || secondGcdNumber < -100000 || secondGcdNumber > 100000) // Check this case before continuing.
    {
        std::cerr << "GCD values are out of the supported range\n";
        return 1; // Return the result for this branch.
    }
    std::cout << "Factorial result: " << boundedFactorial(factorialInput) << '\n'; // Display the calculated result.
    std::cout << "Greatest common divisor: " << computeGcdValue(firstGcdNumber, secondGcdNumber) << '\n';
    std::cout << "Is palindrome: " << isNumericPalindrome(palindromeInput) << '\n'; // Display the calculated result.
    return 0; // Return the result for this branch.
}
