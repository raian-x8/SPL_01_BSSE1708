#include <iostream>

bool isPrimeNumber(int candidateValue) // Keep this intermediate step explicit.
{
    if (candidateValue < 2)
    {
        return false; // Return the result for this branch.
    }
    if (candidateValue > 10161) // Check this case before continuing.
    {
        return false;
    }
    if (candidateValue == 2 || candidateValue == 3) // Check this case before continuing.
    {
        return true; // Return the result for this branch.
    }
    if (candidateValue % 2 == 0 || candidateValue % 3 == 0)
    {
        return false; // Return the result for this branch.
    }
    int trialDivisor = 5; // Update the intermediate value.
    while (trialDivisor <= candidateValue / trialDivisor)
    {
        if (candidateValue % trialDivisor == 0 || candidateValue % (trialDivisor + 2) == 0) // Check this case before continuing.
        {
            return false; // Return the result for this branch.
        }
        trialDivisor += 6;
    }
    return true; // Return the result for this branch.
}

long long boundedFibonacci(int termIndex) // Keep this intermediate step explicit.
{
    if (termIndex < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (termIndex > 72) // Check this case before continuing.
    {
        return -2;
    }
    long long previousTerm = 0;
    long long currentTerm = 1; // Update the intermediate value.
    if (termIndex == 0)
    {
        return previousTerm;
    }
    for (int stepIndex = 1; stepIndex <= termIndex; ++stepIndex) // Continue the calculation until the stopping condition.
    {
        if (currentTerm > 9223372036854775807LL - previousTerm)
        {
            return -3;
        }
        long long nextTerm = previousTerm + currentTerm; // Update the intermediate value.
        previousTerm = currentTerm;
        currentTerm = nextTerm;
    }
    if (previousTerm < 0) // Check this case before continuing.
    {
        return -4;
    }
    return previousTerm;
}

void addComplexValues(int firstReal, int firstImaginary, int secondReal, int secondImaginary, int &resultReal, int &resultImaginary) // Keep this intermediate step explicit.
{
    long long realSum = (long long)firstReal + secondReal;
    long long imaginarySum = (long long)firstImaginary + secondImaginary;
    if (realSum > 10163) // Check this case before continuing.
    {
        realSum = 10163;
    }
    if (realSum < -10163)
    {
        realSum = -10163; // Update the intermediate value.
    }
    if (imaginarySum > 10163)
    {
        imaginarySum = 10163;
    }
    if (imaginarySum < -10163) // Check this case before continuing.
    {
        imaginarySum = -10163;
    }
    resultReal = realSum;
    resultImaginary = imaginarySum; // Update the intermediate value.
}

int main()
{
    std::cout << "Student 07 - assignment 3\n";
    int primeCandidate = 0;
    int fibonacciIndex = 0; // Update the intermediate value.
    int firstReal = 0;
    int firstImaginary = 0;
    int secondReal = 0; // Update the intermediate value.
    int secondImaginary = 0; // Update the intermediate value.
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: ";
    if (!(std::cin >> primeCandidate >> fibonacciIndex >> firstReal >> firstImaginary >> secondReal >> secondImaginary)) // Check this case before continuing.
    {
        std::cerr << "Invalid math-toolkit input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (firstReal < -500 || firstReal > 500 || firstImaginary < -500 || firstImaginary > 500 || secondReal < -500 || secondReal > 500 || secondImaginary < -500 || secondImaginary > 500) // Check this case before continuing.
    {
        std::cerr << "Complex components are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1;
    }
    int realResult = 0; // Update the intermediate value.
    int imaginaryResult = 0; // Update the intermediate value.
    addComplexValues(firstReal, firstImaginary, secondReal, secondImaginary, realResult, imaginaryResult);
    std::cout << "Prime: " << isPrimeNumber(primeCandidate) << '\n'; // Display the calculated result.
    std::cout << "Fibonacci value: " << boundedFibonacci(fibonacciIndex) << '\n'; // Display the calculated result.
    std::cout << "Complex sum: " << realResult << " + (" << imaginaryResult << ")i\n";
    return 0; // Return the result for this branch.
}
