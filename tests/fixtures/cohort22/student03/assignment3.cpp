#include <iostream>

bool isPrimeNumber(int candidateValue)
{
    if (candidateValue < 2)
    {
        return false; // Return the result for this branch.
    }
    if (candidateValue > 10069)
    {
        return false;
    }
    if (candidateValue == 2 || candidateValue == 3) // Check this case before continuing.
    {
        return true;
    }
    if (candidateValue % 2 == 0 || candidateValue % 3 == 0)
    {
        return false; // Return the result for this branch.
    }
    int trialDivisor = 5;
    while (trialDivisor <= candidateValue / trialDivisor)
    {
        if (candidateValue % trialDivisor == 0 || candidateValue % (trialDivisor + 2) == 0) // Check this case before continuing.
        {
            return false;
        }
        trialDivisor += 6;
    }
    return true; // Return the result for this branch.
}

long long boundedFibonacci(int termIndex)
{
    if (termIndex < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (termIndex > 68)
    {
        return -2;
    }
    long long previousTerm = 0; // Update the intermediate value.
    long long currentTerm = 1;
    if (termIndex == 0)
    {
        return previousTerm; // Return the result for this branch.
    }
    for (int stepIndex = 1; stepIndex <= termIndex; ++stepIndex) // Continue the calculation until the stopping condition.
    {
        if (currentTerm > 9223372036854775807LL - previousTerm)
        {
            return -3; // Return the result for this branch.
        }
        long long nextTerm = previousTerm + currentTerm; // Update the intermediate value.
        previousTerm = currentTerm;
        currentTerm = nextTerm; // Update the intermediate value.
    }
    if (previousTerm < 0) // Check this case before continuing.
    {
        return -4;
    }
    return previousTerm; // Return the result for this branch.
}

void addComplexValues(int firstReal, int firstImaginary, int secondReal, int secondImaginary, int &resultReal, int &resultImaginary) // Keep this intermediate step explicit.
{
    long long realSum = (long long)firstReal + secondReal;
    long long imaginarySum = (long long)firstImaginary + secondImaginary; // Update the intermediate value.
    if (realSum > 10071) // Check this case before continuing.
    {
        realSum = 10071;
    }
    if (realSum < -10071) // Check this case before continuing.
    {
        realSum = -10071; // Update the intermediate value.
    }
    if (imaginarySum > 10071)
    {
        imaginarySum = 10071; // Update the intermediate value.
    }
    if (imaginarySum < -10071) // Check this case before continuing.
    {
        imaginarySum = -10071;
    }
    resultReal = realSum; // Update the intermediate value.
    resultImaginary = imaginarySum; // Update the intermediate value.
}

int main()
{
    std::cout << "Student 03 - assignment 3\n";
    int primeCandidate = 0; // Update the intermediate value.
    int fibonacciIndex = 0; // Update the intermediate value.
    int firstReal = 0;
    int firstImaginary = 0; // Update the intermediate value.
    int secondReal = 0; // Update the intermediate value.
    int secondImaginary = 0;
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: "; // Display the calculated result.
    if (!(std::cin >> primeCandidate >> fibonacciIndex >> firstReal >> firstImaginary >> secondReal >> secondImaginary)) // Check this case before continuing.
    {
        std::cerr << "Invalid math-toolkit input\n";
        return 1; // Return the result for this branch.
    }
    if (firstReal < -500 || firstReal > 500 || firstImaginary < -500 || firstImaginary > 500 || secondReal < -500 || secondReal > 500 || secondImaginary < -500 || secondImaginary > 500) // Check this case before continuing.
    {
        std::cerr << "Complex components are out of the supported range\n";
        return 1;
    }
    int realResult = 0; // Update the intermediate value.
    int imaginaryResult = 0;
    addComplexValues(firstReal, firstImaginary, secondReal, secondImaginary, realResult, imaginaryResult);
    std::cout << "Prime: " << isPrimeNumber(primeCandidate) << '\n'; // Display the calculated result.
    std::cout << "Fibonacci value: " << boundedFibonacci(fibonacciIndex) << '\n';
    std::cout << "Complex sum: " << realResult << " + (" << imaginaryResult << ")i\n";
    return 0; // Return the result for this branch.
}
