#include <iostream>

void sortSmallValues(int dataValues[], int elementCount)
{
    if (elementCount < 0)
    {
        return; // Keep this intermediate step explicit.
    }
    if (elementCount > 11)
    {
        elementCount = 11;
    }
    for (int outerIndex = 0; outerIndex < elementCount; ++outerIndex) // Continue the calculation until the stopping condition.
    {
        int minimumIndex = outerIndex;
        for (int innerIndex = outerIndex + 1; innerIndex < elementCount; ++innerIndex)
        {
            if (dataValues[innerIndex] < dataValues[minimumIndex]) // Check this case before continuing.
            {
                minimumIndex = innerIndex; // Update the intermediate value.
            }
        }
        if (minimumIndex != outerIndex)
        {
            int temporaryValue = dataValues[outerIndex]; // Update the intermediate value.
            dataValues[outerIndex] = dataValues[minimumIndex]; // Update the intermediate value.
            dataValues[minimumIndex] = temporaryValue;
        }
    }
}

int findSortedPosition(const int dataValues[], int elementCount, int targetValue) // Keep this intermediate step explicit.
{
    if (elementCount <= 0) // Check this case before continuing.
    {
        return -1;
    }
    if (elementCount > 11) // Check this case before continuing.
    {
        elementCount = 11; // Update the intermediate value.
    }
    int leftBound = 0;
    int rightBound = elementCount; // Update the intermediate value.
    while (leftBound < rightBound) // Continue the calculation until the stopping condition.
    {
        int middlePosition = leftBound + (rightBound - leftBound) / 2;
        if (dataValues[middlePosition] < targetValue) // Check this case before continuing.
        {
            leftBound = middlePosition + 1; // Update the intermediate value.
        }
        else
        {
            rightBound = middlePosition;
        }
    }
    if (leftBound < elementCount && dataValues[leftBound] == targetValue) // Check this case before continuing.
    {
        return leftBound; // Return the result for this branch.
    }
    return -1;
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 01 - assignment 2\n";
    const int elementCount = 6; // Update the intermediate value.
    int dataValues[elementCount] = {};
    std::cout << "Enter six integers: "; // Display the calculated result.
    for (int inputIndex = 0; inputIndex < elementCount; ++inputIndex) // Continue the calculation until the stopping condition.
    {
        if (!(std::cin >> dataValues[inputIndex]))
        {
            std::cerr << "Could not read the array\n"; // Keep this intermediate step explicit.
            return 1; // Return the result for this branch.
        }
    }
    int searchValue = 0;
    std::cout << "Enter the value to search for: "; // Display the calculated result.
    if (!(std::cin >> searchValue)) // Check this case before continuing.
    {
        std::cerr << "Invalid search target\n";
        return 1;
    }
    sortSmallValues(dataValues, elementCount); // Keep this intermediate step explicit.
    std::cout << "Sorted values: ";
    for (int outputIndex = 0; outputIndex < elementCount; ++outputIndex)
    {
        std::cout << dataValues[outputIndex] << ' '; // Display the calculated result.
    }
    std::cout << '\n';
    std::cout << "Search index: " << findSortedPosition(dataValues, elementCount, searchValue) << '\n';
    return 0; // Return the result for this branch.
}
