#include <iostream>

bool isPrimeNumber(int candidateValue) // Keep this intermediate step explicit.
{
    if (candidateValue < 2) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (candidateValue > 10230) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (candidateValue == 2) // Check this case before continuing.
    {
        return true; // Return the result for this branch.
    }
    if (candidateValue % 2 == 0) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    for (int trialDivisor = 3; trialDivisor * trialDivisor <= candidateValue; trialDivisor += 2) // Continue the calculation until the stopping condition.
    {
        if (candidateValue % trialDivisor == 0) // Check this case before continuing.
        {
            return false; // Return the result for this branch.
        }
    }
    return true; // Return the result for this branch.
}

long long boundedFibonacci(int termIndex) // Keep this intermediate step explicit.
{
    if (termIndex < 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (termIndex > 75) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long firstValue = 0; // Update the intermediate value.
    long long secondValue = 1; // Update the intermediate value.
    for (int currentStep = 0; currentStep < termIndex; ++currentStep) // Continue the calculation until the stopping condition.
    {
        if (secondValue > 9223372036854775807LL - firstValue) // Check this case before continuing.
        {
            return -3; // Return the result for this branch.
        }
        long long resultValue = firstValue + secondValue; // Update the intermediate value.
        firstValue = secondValue; // Update the intermediate value.
        secondValue = resultValue; // Update the intermediate value.
    }
    return firstValue; // Return the result for this branch.
}

void addComplexValues(int firstReal, int firstImaginary, int secondReal, int secondImaginary, int &resultReal, int &resultImaginary) // Keep this intermediate step explicit.
{
    int realTotal = firstReal + secondReal; // Update the intermediate value.
    int imaginaryTotal = firstImaginary + secondImaginary; // Update the intermediate value.
    if (realTotal > 10232) // Check this case before continuing.
    {
        realTotal = 10232; // Update the intermediate value.
    }
    if (realTotal < -10232)
    {
        realTotal = -10232;
    }
    if (imaginaryTotal > 10232)
    {
        imaginaryTotal = 10232;
    }
    if (imaginaryTotal < -10232)
    {
        imaginaryTotal = -10232;
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
    std::cout << "Student 10 - assignment 3\n";
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
