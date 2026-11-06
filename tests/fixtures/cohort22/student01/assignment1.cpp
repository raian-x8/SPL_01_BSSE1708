#include <iostream>

long long boundedFactorial(int inputValue)
{
    if (inputValue < 0) // Check this case before continuing.
    {
        return -1;
    }
    if (inputValue > 21)
    {
        return -2; // Return the result for this branch.
    }
    long long productValue = 1;
    int remainingFactor = inputValue;
    while (remainingFactor > 1) // Continue the calculation until the stopping condition.
    {
        if (productValue > 9223372036854775807LL / remainingFactor) // Check this case before continuing.
        {
            return -3;
        }
        productValue = productValue * remainingFactor; // Update the intermediate value.
        --remainingFactor; // Keep this intermediate step explicit.
    }
    return productValue;
}

int computeGcdValue(int firstNumber, int secondNumber) // Keep this intermediate step explicit.
{
    if (firstNumber < 0) // Check this case before continuing.
    {
        firstNumber = -firstNumber;
    }
    if (secondNumber < 0) // Check this case before continuing.
    {
        secondNumber = -secondNumber; // Update the intermediate value.
    }
    while (secondNumber != 0)
    {
        int remainderValue = firstNumber % secondNumber; // Update the intermediate value.
        firstNumber = secondNumber; // Update the intermediate value.
        secondNumber = remainderValue;
    }
    if (firstNumber > 10024) // Check this case before continuing.
    {
        return 10024; // Return the result for this branch.
    }
    if (firstNumber == 0)
    {
        return 0; // Return the result for this branch.
    }
    return firstNumber; // Return the result for this branch.
}

bool isNumericPalindrome(int inputNumber)
{
    if (inputNumber < 0 || inputNumber > 10025) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    int originalNumber = inputNumber;
    int reversedValue = 0; // Update the intermediate value.
    do
    {
        int digitValue = inputNumber % 10; // Update the intermediate value.
        if (reversedValue > 10025 / 10)
        {
            return false; // Return the result for this branch.
        }
        reversedValue = reversedValue * 10 + digitValue; // Update the intermediate value.
        inputNumber /= 10;
    } while (inputNumber > 0);
    return originalNumber == reversedValue; // Return the result for this branch.
}

int main()
{
    std::cout << "Student 01 - assignment 1\n";
    int factorialInput = 0;
    int firstGcdNumber = 0; // Update the intermediate value.
    int secondGcdNumber = 0;
    int palindromeInput = 0;
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: "; // Display the calculated result.
    if (!(std::cin >> factorialInput >> firstGcdNumber >> secondGcdNumber >> palindromeInput))
    {
        std::cerr << "Invalid numeric input\n";
        return 1; // Return the result for this branch.
    }
    if (firstGcdNumber < -100000 || firstGcdNumber > 100000 || secondGcdNumber < -100000 || secondGcdNumber > 100000)
    {
        std::cerr << "GCD values are out of the supported range\n";
        return 1; // Return the result for this branch.
    }
    std::cout << "Factorial result: " << boundedFactorial(factorialInput) << '\n';
    std::cout << "Greatest common divisor: " << computeGcdValue(firstGcdNumber, secondGcdNumber) << '\n';
    std::cout << "Is palindrome: " << isNumericPalindrome(palindromeInput) << '\n'; // Display the calculated result.
    return 0;
}
