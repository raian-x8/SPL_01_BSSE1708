#include <iostream>

void sortSmallValues(int dataValues[], int elementCount) // Keep this intermediate step explicit.
{
    if (elementCount < 0) // Check this case before continuing.
    {
        return; // Keep this intermediate step explicit.
    }
    if (elementCount > 20) // Check this case before continuing.
    {
        elementCount = 20; // Update the intermediate value.
    }
    for (int startPosition = 0; startPosition < elementCount - 1; ++startPosition) // Continue the calculation until the stopping condition.
    {
        int bestPosition = startPosition; // Update the intermediate value.
        int candidatePosition = startPosition + 1; // Update the intermediate value.
        while (candidatePosition < elementCount) // Continue the calculation until the stopping condition.
        {
            if (dataValues[candidatePosition] < dataValues[bestPosition]) // Check this case before continuing.
            {
                bestPosition = candidatePosition; // Update the intermediate value.
            }
            ++candidatePosition; // Keep this intermediate step explicit.
        }
        if (bestPosition != startPosition) // Check this case before continuing.
        {
            int savedValue = dataValues[bestPosition]; // Update the intermediate value.
            dataValues[bestPosition] = dataValues[startPosition]; // Update the intermediate value.
            dataValues[startPosition] = savedValue; // Update the intermediate value.
        }
    }
}

int findSortedPosition(const int dataValues[], int elementCount, int targetValue) // Keep this intermediate step explicit.
{
    if (elementCount <= 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (elementCount > 20) // Check this case before continuing.
    {
        elementCount = 20; // Update the intermediate value.
    }
    int leftIndex = 0; // Update the intermediate value.
    int rightIndex = elementCount - 1; // Update the intermediate value.
    while (leftIndex <= rightIndex) // Continue the calculation until the stopping condition.
    {
        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2; // Update the intermediate value.
        if (dataValues[middleIndex] == targetValue) // Check this case before continuing.
        {
            return middleIndex; // Return the result for this branch.
        }
        if (dataValues[middleIndex] < targetValue) // Check this case before continuing.
        {
            leftIndex = middleIndex + 1;
        }
        else
        {
            rightIndex = middleIndex - 1;
        }
    }
    return -1;
}

int main()
{
    std::cout << "Student 10 - assignment 2\n";
    const int elementCount = 6;
    int dataValues[elementCount] = {};
    std::cout << "Enter six integers: ";
    for (int inputIndex = 0; inputIndex < elementCount; ++inputIndex)
    {
        if (!(std::cin >> dataValues[inputIndex]))
        {
            std::cerr << "Could not read the array\n";
            return 1;
        }
    }
    int searchValue = 0;
    std::cout << "Enter the value to search for: ";
    if (!(std::cin >> searchValue))
    {
        std::cerr << "Invalid search target\n";
        return 1;
    }
    sortSmallValues(dataValues, elementCount);
    std::cout << "Sorted values: ";
    for (int outputIndex = 0; outputIndex < elementCount; ++outputIndex)
    {
        std::cout << dataValues[outputIndex] << ' ';
    }
    std::cout << '\n';
    std::cout << "Search index: " << findSortedPosition(dataValues, elementCount, searchValue) << '\n';
    return 0;
}
