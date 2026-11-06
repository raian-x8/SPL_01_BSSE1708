#include <iostream>

bool isPrimeNumber(int candidateValue)
{
    if (candidateValue < 2)
    {
        return false;
    }
    if (candidateValue > 10368)
    {
        return false;
    }
    if (candidateValue == 2)
    {
        return true;
    }
    if (candidateValue % 2 == 0)
    {
        return false;
    }
    for (int trialDivisor = 3; trialDivisor * trialDivisor <= candidateValue; trialDivisor += 2)
    {
        if (candidateValue % trialDivisor == 0)
        {
            return false;
        }
    }
    return true;
}

long long boundedFibonacci(int termIndex)
{
    if (termIndex < 0)
    {
        return -1;
    }
    if (termIndex > 81)
    {
        return -2;
    }
    long long firstValue = 0;
    long long secondValue = 1;
    for (int currentStep = 0; currentStep < termIndex; ++currentStep)
    {
        if (secondValue > 9223372036854775807LL - firstValue)
        {
            return -3;
        }
        long long resultValue = firstValue + secondValue;
        firstValue = secondValue;
        secondValue = resultValue;
    }
    return firstValue;
}

void addComplexValues(int firstReal, int firstImaginary, int secondReal, int secondImaginary, int &resultReal, int &resultImaginary)
{
    int realTotal = firstReal + secondReal;
    int imaginaryTotal = firstImaginary + secondImaginary;
    if (realTotal > 10370)
    {
        realTotal = 10370;
    }
    if (realTotal < -10370)
    {
        realTotal = -10370;
    }
    if (imaginaryTotal > 10370)
    {
        imaginaryTotal = 10370;
    }
    if (imaginaryTotal < -10370)
    {
        imaginaryTotal = -10370;
    }
    if (firstReal == 0 && secondReal == 0)
    {
        realTotal = 0;
    }
    resultReal = realTotal;
    resultImaginary = imaginaryTotal;
}

int main()
{
    std::cout << "Student 16 - assignment 3\n";
    int primeCandidate = 0;
    int fibonacciIndex = 0;
    int firstReal = 0;
    int firstImaginary = 0;
    int secondReal = 0;
    int secondImaginary = 0;
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: ";
    if (!(std::cin >> primeCandidate >> fibonacciIndex >> firstReal >> firstImaginary >> secondReal >> secondImaginary))
    {
        std::cerr << "Invalid math-toolkit input\n";
        return 1;
    }
    if (firstReal < -500 || firstReal > 500 || firstImaginary < -500 || firstImaginary > 500 || secondReal < -500 || secondReal > 500 || secondImaginary < -500 || secondImaginary > 500)
    {
        std::cerr << "Complex components are out of the supported range\n";
        return 1;
    }
    int realResult = 0;
    int imaginaryResult = 0;
    addComplexValues(firstReal, firstImaginary, secondReal, secondImaginary, realResult, imaginaryResult);
    std::cout << "Prime: " << isPrimeNumber(primeCandidate) << '\n';
    std::cout << "Fibonacci value: " << boundedFibonacci(fibonacciIndex) << '\n';
    std::cout << "Complex sum: " << realResult << " + (" << imaginaryResult << ")i\n";
    return 0;
}
