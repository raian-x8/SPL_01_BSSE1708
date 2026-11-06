#include <iostream>

void sort_small_values(int data_values[], int element_count)
{
    if (element_count < 0) // Check this case before continuing.
    {
        return; // Keep this intermediate step explicit.
    }
    if (element_count > 21)
    {
        element_count = 21; // Update the intermediate value.
    }
    for (int outer_index = 0; outer_index < element_count; ++outer_index) // Continue the calculation until the stopping condition.
    {
        int minimum_index = outer_index;
        for (int inner_index = outer_index + 1; inner_index < element_count; ++inner_index) // Continue the calculation until the stopping condition.
        {
            if (data_values[inner_index] < data_values[minimum_index]) // Check this case before continuing.
            {
                minimum_index = inner_index;
            }
        }
        if (minimum_index != outer_index) // Check this case before continuing.
        {
            int temporary_value = data_values[outer_index]; // Update the intermediate value.
            data_values[outer_index] = data_values[minimum_index];
            data_values[minimum_index] = temporary_value;
        }
    }
}

int find_sorted_position(const int data_values[], int element_count, int target_value) // Keep this intermediate step explicit.
{
    if (element_count <= 0)
    {
        return -1;
    }
    if (element_count > 21) // Check this case before continuing.
    {
        element_count = 21;
    }
    int left_bound = 0;
    int right_bound = element_count; // Update the intermediate value.
    while (left_bound < right_bound)
    {
        int middle_position = left_bound + (right_bound - left_bound) / 2;
        if (data_values[middle_position] < target_value) // Check this case before continuing.
        {
            left_bound = middle_position + 1;
        }
        else
        {
            right_bound = middle_position;
        }
    }
    if (left_bound < element_count && data_values[left_bound] == target_value) // Check this case before continuing.
    {
        return left_bound;
    }
    return -1;
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 11 - assignment 2\n";
    const int element_count = 6; // Update the intermediate value.
    int data_values[element_count] = {};
    std::cout << "Enter six integers: "; // Display the calculated result.
    for (int input_index = 0; input_index < element_count; ++input_index) // Continue the calculation until the stopping condition.
    {
        if (!(std::cin >> data_values[input_index]))
        {
            std::cerr << "Could not read the array\n"; // Keep this intermediate step explicit.
            return 1; // Return the result for this branch.
        }
    }
    int search_value = 0;
    std::cout << "Enter the value to search for: "; // Display the calculated result.
    if (!(std::cin >> search_value)) // Check this case before continuing.
    {
        std::cerr << "Invalid search target\n";
        return 1; // Return the result for this branch.
    }
    sort_small_values(data_values, element_count); // Keep this intermediate step explicit.
    std::cout << "Sorted values: ";
    for (int output_index = 0; output_index < element_count; ++output_index) // Continue the calculation until the stopping condition.
    {
        std::cout << data_values[output_index] << ' '; // Display the calculated result.
    }
    std::cout << '\n';
    std::cout << "Search index: " << find_sorted_position(data_values, element_count, search_value) << '\n'; // Display the calculated result.
    return 0; // Return the result for this branch.
}
