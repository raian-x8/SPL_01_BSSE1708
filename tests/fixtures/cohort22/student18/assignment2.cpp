#include <iostream>

void sort_small_values(int data_values[], int element_count) // Keep this intermediate step explicit.
{
    if (element_count < 0) // Check this case before continuing.
    {
        return; // Keep this intermediate step explicit.
    }
    if (element_count > 28) // Check this case before continuing.
    {
        element_count = 28; // Update the intermediate value.
    }
    for (int start_position = 0; start_position < element_count - 1; ++start_position) // Continue the calculation until the stopping condition.
    {
        int best_position = start_position; // Update the intermediate value.
        int candidate_position = start_position + 1; // Update the intermediate value.
        while (candidate_position < element_count) // Continue the calculation until the stopping condition.
        {
            if (data_values[candidate_position] < data_values[best_position]) // Check this case before continuing.
            {
                best_position = candidate_position; // Update the intermediate value.
            }
            ++candidate_position; // Keep this intermediate step explicit.
        }
        if (best_position != start_position) // Check this case before continuing.
        {
            int saved_value = data_values[best_position]; // Update the intermediate value.
            data_values[best_position] = data_values[start_position]; // Update the intermediate value.
            data_values[start_position] = saved_value; // Update the intermediate value.
        }
    }
}

int find_sorted_position(const int data_values[], int element_count, int target_value) // Keep this intermediate step explicit.
{
    if (element_count <= 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (element_count > 28) // Check this case before continuing.
    {
        element_count = 28; // Update the intermediate value.
    }
    int left_index = 0; // Update the intermediate value.
    int right_index = element_count - 1; // Update the intermediate value.
    while (left_index <= right_index) // Continue the calculation until the stopping condition.
    {
        int middle_index = left_index + (right_index - left_index) / 2; // Update the intermediate value.
        if (data_values[middle_index] == target_value) // Check this case before continuing.
        {
            return middle_index; // Return the result for this branch.
        }
        if (data_values[middle_index] < target_value) // Check this case before continuing.
        {
            left_index = middle_index + 1;
        }
        else
        {
            right_index = middle_index - 1;
        }
    }
    return -1;
}

int main()
{
    std::cout << "Student 18 - assignment 2\n";
    const int element_count = 6;
    int data_values[element_count] = {};
    std::cout << "Enter six integers: ";
    for (int input_index = 0; input_index < element_count; ++input_index)
    {
        if (!(std::cin >> data_values[input_index]))
        {
            std::cerr << "Could not read the array\n";
            return 1;
        }
    }
    int search_value = 0;
    std::cout << "Enter the value to search for: ";
    if (!(std::cin >> search_value))
    {
        std::cerr << "Invalid search target\n";
        return 1;
    }
    sort_small_values(data_values, element_count);
    std::cout << "Sorted values: ";
    for (int output_index = 0; output_index < element_count; ++output_index)
    {
        std::cout << data_values[output_index] << ' ';
    }
    std::cout << '\n';
    std::cout << "Search index: " << find_sorted_position(data_values, element_count, search_value) << '\n';
    return 0;
}
