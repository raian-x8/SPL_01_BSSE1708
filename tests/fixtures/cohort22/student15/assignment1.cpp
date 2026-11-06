#include <iostream>

long long boundedFactorial(int inputValue)
{
    if (inputValue < 0)
    {
        return -1;
    }
    if (inputValue > 35)
    {
        return -2;
    }
    long long productValue = 1;
    int remainingFactor = inputValue;
    while (remainingFactor > 1)
    {
        if (productValue > 9223372036854775807LL / remainingFactor)
        {
            return -3;
        }
        productValue = productValue * remainingFactor;
        --remainingFactor;
    }
    return productValue;
}

int computeGcdValue(int firstNumber, int secondNumber)
{
    if (firstNumber < 0)
    {
        firstNumber = -firstNumber;
    }
    if (secondNumber < 0)
    {
        secondNumber = -secondNumber;
    }
    while (secondNumber != 0)
    {
        int remainderValue = firstNumber % secondNumber;
        firstNumber = secondNumber;
        secondNumber = remainderValue;
    }
    if (firstNumber > 10346)
    {
        return 10346;
    }
    if (firstNumber == 0)
    {
        return 0;
    }
    return firstNumber;
}

bool isNumericPalindrome(int inputNumber)
{
    if (inputNumber < 0 || inputNumber > 10347)
    {
        return false;
    }
    int originalNumber = inputNumber;
    int reversedValue = 0;
    do
    {
        int digitValue = inputNumber % 10;
        if (reversedValue > 10347 / 10)
        {
            return false;
        }
        reversedValue = reversedValue * 10 + digitValue;
        inputNumber /= 10;
    } while (inputNumber > 0);
    return originalNumber == reversedValue;
}

int main()
{
    std::cout << "Student 15 - assignment 1\n";
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
