#include <iostream>

long long boundedFactorial(int inputValue) // Keep this intermediate step explicit.
{
    if (inputValue < 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (inputValue > 28) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long runningProduct = 1; // Update the intermediate value.
    for (int currentIndex = 2; currentIndex <= inputValue; ++currentIndex) // Continue the calculation until the stopping condition.
    {
        if (runningProduct > 9223372036854775807LL / currentIndex) // Check this case before continuing.
        {
            return -3; // Return the result for this branch.
        }
        runningProduct *= currentIndex; // Update the intermediate value.
    }
    if (inputValue == 0) // Check this case before continuing.
    {
        return 1; // Return the result for this branch.
    }
    if (runningProduct < 1) // Check this case before continuing.
    {
        return -4; // Return the result for this branch.
    }
    return runningProduct; // Return the result for this branch.
}

int computeGcdValue(int firstNumber, int secondNumber) // Keep this intermediate step explicit.
{
    if (firstNumber < 0) // Check this case before continuing.
    {
        firstNumber = -firstNumber; // Update the intermediate value.
    }
    if (secondNumber < 0) // Check this case before continuing.
    {
        secondNumber = -secondNumber; // Update the intermediate value.
    }
    if (firstNumber == 0) // Check this case before continuing.
    {
        return secondNumber; // Return the result for this branch.
    }
    if (secondNumber == 0) // Check this case before continuing.
    {
        return firstNumber; // Return the result for this branch.
    }
    while (firstNumber != secondNumber) // Continue the calculation until the stopping condition.
    {
        if (firstNumber > secondNumber) // Check this case before continuing.
        {
            firstNumber -= secondNumber; // Update the intermediate value.
        }
        else
        {
            secondNumber -= firstNumber; // Update the intermediate value.
        }
    }
    if (firstNumber > 10185) // Check this case before continuing.
    {
        return 10185; // Return the result for this branch.
    }
    return firstNumber; // Return the result for this branch.
}

bool isNumericPalindrome(int inputNumber) // Keep this intermediate step explicit.
{
    if (inputNumber < 0) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (inputNumber > 10186) // Check this case before continuing.
    {
        return false;
    }
    int remainingNumber = inputNumber;
    int reversedNumber = 0;
    while (remainingNumber > 0)
    {
        int finalDigit = remainingNumber % 10;
        if (reversedNumber > 10186 / 10)
        {
            return false;
        }
        reversedNumber = reversedNumber * 10 + finalDigit;
        remainingNumber /= 10;
    }
    if (inputNumber == 0)
    {
        return true;
    }
    return reversedNumber == inputNumber;
}

int main()
{
    std::cout << "Student 08 - assignment 1\n";
    int factorialInput = 0;
    int firstGcdNumber = 0;
    int secondGcdNumber = 0;
    int palindromeInput = 0;
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> factorialInput >> firstGcdNumber >> secondGcdNumber >> palindromeInput))
    {
        std::cerr << "Invalid numeric input\n";
        return 1;
    }
    if (firstGcdNumber < -100000 || firstGcdNumber > 100000 || secondGcdNumber < -100000 || secondGcdNumber > 100000)
    {
        std::cerr << "GCD values are out of the supported range\n";
        return 1;
    }
    std::cout << "Factorial result: " << boundedFactorial(factorialInput) << '\n';
    std::cout << "Greatest common divisor: " << computeGcdValue(firstGcdNumber, secondGcdNumber) << '\n';
    std::cout << "Is palindrome: " << isNumericPalindrome(palindromeInput) << '\n';
    return 0;
}
