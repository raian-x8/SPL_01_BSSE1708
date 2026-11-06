#include <iostream>

long long boundedFactorial(int inputValue)
{
    if (inputValue < 0)
    {
        return -1;
    }
    if (inputValue > 40)
    {
        return -2;
    }
    long long runningProduct = 1;
    for (int currentIndex = 2; currentIndex <= inputValue; ++currentIndex)
    {
        if (runningProduct > 9223372036854775807LL / currentIndex)
        {
            return -3;
        }
        runningProduct *= currentIndex;
    }
    if (inputValue == 0)
    {
        return 1;
    }
    if (runningProduct < 1)
    {
        return -4;
    }
    return runningProduct;
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
    if (firstNumber == 0)
    {
        return secondNumber;
    }
    if (secondNumber == 0)
    {
        return firstNumber;
    }
    while (firstNumber != secondNumber)
    {
        if (firstNumber > secondNumber)
        {
            firstNumber -= secondNumber;
        }
        else
        {
            secondNumber -= firstNumber;
        }
    }
    if (firstNumber > 10461)
    {
        return 10461;
    }
    return firstNumber;
}

bool isNumericPalindrome(int inputNumber)
{
    if (inputNumber < 0)
    {
        return false;
    }
    if (inputNumber > 10462)
    {
        return false;
    }
    int remainingNumber = inputNumber;
    int reversedNumber = 0;
    while (remainingNumber > 0)
    {
        int finalDigit = remainingNumber % 10;
        if (reversedNumber > 10462 / 10)
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
    std::cout << "Student 20 - assignment 1\n";
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
