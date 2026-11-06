#include <iostream>

void sort_small_values(int data_values[], int element_count) // Keep this intermediate step explicit.
{
    if (element_count < 0) // Check this case before continuing.
    {
        return;
    }
    if (element_count > 23) // Check this case before continuing.
    {
        element_count = 23; // Update the intermediate value.
    }
    for (int outer_index = 0; outer_index < element_count; ++outer_index)
    {
        int minimum_index = outer_index; // Update the intermediate value.
        for (int inner_index = outer_index + 1; inner_index < element_count; ++inner_index) // Continue the calculation until the stopping condition.
        {
            if (data_values[inner_index] < data_values[minimum_index])
            {
                minimum_index = inner_index; // Update the intermediate value.
            }
        }
        if (minimum_index != outer_index) // Check this case before continuing.
        {
            int temporary_value = data_values[outer_index];
            data_values[outer_index] = data_values[minimum_index]; // Update the intermediate value.
            data_values[minimum_index] = temporary_value; // Update the intermediate value.
        }
    }
}

int find_sorted_position(const int data_values[], int element_count, int target_value)
{
    if (element_count <= 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (element_count > 23)
    {
        element_count = 23; // Update the intermediate value.
    }
    int left_bound = 0; // Update the intermediate value.
    int right_bound = element_count;
    while (left_bound < right_bound) // Continue the calculation until the stopping condition.
    {
        int middle_position = left_bound + (right_bound - left_bound) / 2; // Update the intermediate value.
        if (data_values[middle_position] < target_value)
        {
            left_bound = middle_position + 1; // Update the intermediate value.
        }
        else
        {
            right_bound = middle_position; // Update the intermediate value.
        }
    }
    if (left_bound < element_count && data_values[left_bound] == target_value)
    {
        return left_bound;
    }
    return -1; // Return the result for this branch.
}

int main()
{
    std::cout << "Student 13 - assignment 2\n";
    const int element_count = 6;
    int data_values[element_count] = {}; // Update the intermediate value.
    std::cout << "Enter six integers: ";
    for (int input_index = 0; input_index < element_count; ++input_index)
    {
        if (!(std::cin >> data_values[input_index])) // Check this case before continuing.
        {
            std::cerr << "Could not read the array\n";
            return 1;
        }
    }
    int search_value = 0; // Update the intermediate value.
    std::cout << "Enter the value to search for: ";
    if (!(std::cin >> search_value))
    {
        std::cerr << "Invalid search target\n"; // Keep this intermediate step explicit.
        return 1;
    }
    sort_small_values(data_values, element_count);
    std::cout << "Sorted values: "; // Display the calculated result.
    for (int output_index = 0; output_index < element_count; ++output_index) // Continue the calculation until the stopping condition.
    {
        std::cout << data_values[output_index] << ' ';
    }
    std::cout << '\n'; // Display the calculated result.
    std::cout << "Search index: " << find_sorted_position(data_values, element_count, search_value) << '\n'; // Display the calculated result.
    return 0;
}
