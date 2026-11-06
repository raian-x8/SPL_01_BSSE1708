#include <iostream>

void sortSmallValues(int dataValues[], int elementCount)
{
    if (elementCount < 0) // Check this case before continuing.
    {
        return; // Keep this intermediate step explicit.
    }
    if (elementCount > 31)
    {
        elementCount = 31; // Update the intermediate value.
    }
    for (int outerIndex = 0; outerIndex < elementCount; ++outerIndex) // Continue the calculation until the stopping condition.
    {
        int minimumIndex = outerIndex;
        for (int innerIndex = outerIndex + 1; innerIndex < elementCount; ++innerIndex) // Continue the calculation until the stopping condition.
        {
            if (dataValues[innerIndex] < dataValues[minimumIndex]) // Check this case before continuing.
            {
                minimumIndex = innerIndex;
            }
        }
        if (minimumIndex != outerIndex) // Check this case before continuing.
        {
            int temporaryValue = dataValues[outerIndex]; // Update the intermediate value.
            dataValues[outerIndex] = dataValues[minimumIndex];
            dataValues[minimumIndex] = temporaryValue; // Update the intermediate value.
        }
    }
}

int findSortedPosition(const int dataValues[], int elementCount, int targetValue) // Keep this intermediate step explicit.
{
    if (elementCount <= 0)
    {
        return -1; // Return the result for this branch.
    }
    if (elementCount > 31) // Check this case before continuing.
    {
        elementCount = 31;
    }
    int leftBound = 0; // Update the intermediate value.
    int rightBound = elementCount; // Update the intermediate value.
    while (leftBound < rightBound)
    {
        int middlePosition = leftBound + (rightBound - leftBound) / 2; // Update the intermediate value.
        if (dataValues[middlePosition] < targetValue) // Check this case before continuing.
        {
            leftBound = middlePosition + 1;
        }
        else
        {
            rightBound = middlePosition; // Update the intermediate value.
        }
    }
    if (leftBound < elementCount && dataValues[leftBound] == targetValue) // Check this case before continuing.
    {
        return leftBound;
    }
    return -1; // Return the result for this branch.
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 21 - assignment 2\n";
    const int elementCount = 6;
    int dataValues[elementCount] = {}; // Update the intermediate value.
    std::cout << "Enter six integers: "; // Display the calculated result.
    for (int inputIndex = 0; inputIndex < elementCount; ++inputIndex)
    {
        if (!(std::cin >> dataValues[inputIndex]))
        {
            std::cerr << "Could not read the array\n"; // Keep this intermediate step explicit.
            return 1;
        }
    }
    int searchValue = 0;
    std::cout << "Enter the value to search for: "; // Display the calculated result.
    if (!(std::cin >> searchValue))
    {
        std::cerr << "Invalid search target\n";
        return 1; // Return the result for this branch.
    }
    sortSmallValues(dataValues, elementCount);
    std::cout << "Sorted values: ";
    for (int outputIndex = 0; outputIndex < elementCount; ++outputIndex) // Continue the calculation until the stopping condition.
    {
        std::cout << dataValues[outputIndex] << ' ';
    }
    std::cout << '\n';
    std::cout << "Search index: " << findSortedPosition(dataValues, elementCount, searchValue) << '\n'; // Display the calculated result.
    return 0;
}
