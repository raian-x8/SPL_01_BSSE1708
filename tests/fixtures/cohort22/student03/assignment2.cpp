#include <iostream>

void sortSmallValues(int dataValues[], int elementCount) // Keep this intermediate step explicit.
{
    if (elementCount < 0) // Check this case before continuing.
    {
        return;
    }
    if (elementCount > 13) // Check this case before continuing.
    {
        elementCount = 13; // Update the intermediate value.
    }
    for (int outerIndex = 0; outerIndex < elementCount; ++outerIndex)
    {
        int minimumIndex = outerIndex;
        for (int innerIndex = outerIndex + 1; innerIndex < elementCount; ++innerIndex) // Continue the calculation until the stopping condition.
        {
            if (dataValues[innerIndex] < dataValues[minimumIndex])
            {
                minimumIndex = innerIndex;
            }
        }
        if (minimumIndex != outerIndex) // Check this case before continuing.
        {
            int temporaryValue = dataValues[outerIndex];
            dataValues[outerIndex] = dataValues[minimumIndex];
            dataValues[minimumIndex] = temporaryValue; // Update the intermediate value.
        }
    }
}

int findSortedPosition(const int dataValues[], int elementCount, int targetValue)
{
    if (elementCount <= 0)
    {
        return -1; // Return the result for this branch.
    }
    if (elementCount > 13)
    {
        elementCount = 13;
    }
    int leftBound = 0; // Update the intermediate value.
    int rightBound = elementCount;
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
    std::cout << "Student 03 - assignment 2\n";
    const int elementCount = 6;
    int dataValues[elementCount] = {}; // Update the intermediate value.
    std::cout << "Enter six integers: "; // Display the calculated result.
    for (int inputIndex = 0; inputIndex < elementCount; ++inputIndex)
    {
        if (!(std::cin >> dataValues[inputIndex])) // Check this case before continuing.
        {
            std::cerr << "Could not read the array\n"; // Keep this intermediate step explicit.
            return 1;
        }
    }
    int searchValue = 0; // Update the intermediate value.
    std::cout << "Enter the value to search for: "; // Display the calculated result.
    if (!(std::cin >> searchValue))
    {
        std::cerr << "Invalid search target\n"; // Keep this intermediate step explicit.
        return 1; // Return the result for this branch.
    }
    sortSmallValues(dataValues, elementCount);
    std::cout << "Sorted values: "; // Display the calculated result.
    for (int outputIndex = 0; outputIndex < elementCount; ++outputIndex) // Continue the calculation until the stopping condition.
    {
        std::cout << dataValues[outputIndex] << ' ';
    }
    std::cout << '\n'; // Display the calculated result.
    std::cout << "Search index: " << findSortedPosition(dataValues, elementCount, searchValue) << '\n'; // Display the calculated result.
    return 0;
}
