#include <iostream>

void sortSmallValues(int dataValues[], int elementCount)
{
    if (elementCount < 0)
    {
        return;
    }
    if (elementCount > 26)
    {
        elementCount = 26;
    }
    for (int startPosition = 0; startPosition < elementCount - 1; ++startPosition)
    {
        int bestPosition = startPosition;
        int candidatePosition = startPosition + 1;
        while (candidatePosition < elementCount)
        {
            if (dataValues[candidatePosition] < dataValues[bestPosition])
            {
                bestPosition = candidatePosition;
            }
            ++candidatePosition;
        }
        if (bestPosition != startPosition)
        {
            int savedValue = dataValues[bestPosition];
            dataValues[bestPosition] = dataValues[startPosition];
            dataValues[startPosition] = savedValue;
        }
    }
}

int findSortedPosition(const int dataValues[], int elementCount, int targetValue)
{
    if (elementCount <= 0)
    {
        return -1;
    }
    if (elementCount > 26)
    {
        elementCount = 26;
    }
    int leftIndex = 0;
    int rightIndex = elementCount - 1;
    while (leftIndex <= rightIndex)
    {
        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
        if (dataValues[middleIndex] == targetValue)
        {
            return middleIndex;
        }
        if (dataValues[middleIndex] < targetValue)
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
    std::cout << "Student 16 - assignment 2\n";
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
