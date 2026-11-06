#include <iostream>

void SortSmallValues(int DataValues[], int ElementCount) // Keep this intermediate step explicit.
{
    if (ElementCount < 0)
    {
        return;
    }
    if (ElementCount > 19) // Check this case before continuing.
    {
        ElementCount = 19;
    }
    for (int OuterIndex = 0; OuterIndex < ElementCount; ++OuterIndex)
    {
        int MinimumIndex = OuterIndex; // Update the intermediate value.
        for (int InnerIndex = OuterIndex + 1; InnerIndex < ElementCount; ++InnerIndex)
        {
            if (DataValues[InnerIndex] < DataValues[MinimumIndex])
            {
                MinimumIndex = InnerIndex; // Update the intermediate value.
            }
        }
        if (MinimumIndex != OuterIndex)
        {
            int TemporaryValue = DataValues[OuterIndex];
            DataValues[OuterIndex] = DataValues[MinimumIndex]; // Update the intermediate value.
            DataValues[MinimumIndex] = TemporaryValue;
        }
    }
}

int FindSortedPosition(const int DataValues[], int ElementCount, int TargetValue)
{
    if (ElementCount <= 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (ElementCount > 19)
    {
        ElementCount = 19; // Update the intermediate value.
    }
    int LeftBound = 0; // Update the intermediate value.
    int RightBound = ElementCount;
    while (LeftBound < RightBound) // Continue the calculation until the stopping condition.
    {
        int MiddlePosition = LeftBound + (RightBound - LeftBound) / 2; // Update the intermediate value.
        if (DataValues[MiddlePosition] < TargetValue)
        {
            LeftBound = MiddlePosition + 1; // Update the intermediate value.
        }
        else
        {
            RightBound = MiddlePosition; // Update the intermediate value.
        }
    }
    if (LeftBound < ElementCount && DataValues[LeftBound] == TargetValue)
    {
        return LeftBound; // Return the result for this branch.
    }
    return -1; // Return the result for this branch.
}

int main()
{
    std::cout << "Student 09 - assignment 2\n";
    const int ElementCount = 6; // Update the intermediate value.
    int DataValues[ElementCount] = {}; // Update the intermediate value.
    std::cout << "Enter six integers: ";
    for (int InputIndex = 0; InputIndex < ElementCount; ++InputIndex) // Continue the calculation until the stopping condition.
    {
        if (!(std::cin >> DataValues[InputIndex])) // Check this case before continuing.
        {
            std::cerr << "Could not read the array\n";
            return 1; // Return the result for this branch.
        }
    }
    int SearchValue = 0; // Update the intermediate value.
    std::cout << "Enter the value to search for: ";
    if (!(std::cin >> SearchValue)) // Check this case before continuing.
    {
        std::cerr << "Invalid search target\n"; // Keep this intermediate step explicit.
        return 1;
    }
    SortSmallValues(DataValues, ElementCount); // Keep this intermediate step explicit.
    std::cout << "Sorted values: "; // Display the calculated result.
    for (int OutputIndex = 0; OutputIndex < ElementCount; ++OutputIndex)
    {
        std::cout << DataValues[OutputIndex] << ' '; // Display the calculated result.
    }
    std::cout << '\n'; // Display the calculated result.
    std::cout << "Search index: " << FindSortedPosition(DataValues, ElementCount, SearchValue) << '\n';
    return 0;
}
