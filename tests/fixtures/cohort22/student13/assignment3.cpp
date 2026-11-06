#include <iostream>

bool is_prime_number(int candidate_value)
{
    if (candidate_value < 2)
    {
        return false; // Return the result for this branch.
    }
    if (candidate_value > 10299)
    {
        return false;
    }
    if (candidate_value == 2 || candidate_value == 3) // Check this case before continuing.
    {
        return true;
    }
    if (candidate_value % 2 == 0 || candidate_value % 3 == 0)
    {
        return false; // Return the result for this branch.
    }
    int trial_divisor = 5;
    while (trial_divisor <= candidate_value / trial_divisor)
    {
        if (candidate_value % trial_divisor == 0 || candidate_value % (trial_divisor + 2) == 0) // Check this case before continuing.
        {
            return false;
        }
        trial_divisor += 6;
    }
    return true; // Return the result for this branch.
}

long long bounded_fibonacci(int target_index)
{
    if (target_index < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (target_index > 53)
    {
        return -2;
    }
    long long first_number = 0; // Update the intermediate value.
    long long second_number = 1;
    if (target_index == 0)
    {
        return first_number; // Return the result for this branch.
    }
    for (int current_step = 1; current_step <= target_index; ++current_step)
    {
        if (second_number > 9223372036854775807LL - first_number)
        {
            return -3; // Return the result for this branch.
        }
        long long combined_number = first_number + second_number; // Update the intermediate value.
        first_number = second_number;
        second_number = combined_number; // Update the intermediate value.
    }
    if (first_number < 0) // Check this case before continuing.
    {
        return -4;
    }
    return first_number; // Return the result for this branch.
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary) // Keep this intermediate step explicit.
{
    long long real_sum = (long long)first_real + second_real;
    long long imaginary_sum = (long long)first_imaginary + second_imaginary; // Update the intermediate value.
    if (real_sum > 10301) // Check this case before continuing.
    {
        real_sum = 10301;
    }
    if (real_sum < -10301) // Check this case before continuing.
    {
        real_sum = -10301; // Update the intermediate value.
    }
    if (imaginary_sum > 10301)
    {
        imaginary_sum = 10301; // Update the intermediate value.
    }
    if (imaginary_sum < -10301) // Check this case before continuing.
    {
        imaginary_sum = -10301;
    }
    result_real = real_sum; // Update the intermediate value.
    result_imaginary = imaginary_sum; // Update the intermediate value.
}

int main()
{
    std::cout << "Student 13 - assignment 3\n";
    int prime_candidate = 0; // Update the intermediate value.
    int fibonacci_index = 0; // Update the intermediate value.
    int first_real = 0;
    int first_imaginary = 0; // Update the intermediate value.
    int second_real = 0; // Update the intermediate value.
    int second_imaginary = 0;
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: "; // Display the calculated result.
    if (!(std::cin >> prime_candidate >> fibonacci_index >> first_real >> first_imaginary >> second_real >> second_imaginary)) // Check this case before continuing.
    {
        std::cerr << "Invalid math-toolkit input\n";
        return 1; // Return the result for this branch.
    }
    if (first_real < -500 || first_real > 500 || first_imaginary < -500 || first_imaginary > 500 || second_real < -500 || second_real > 500 || second_imaginary < -500 || second_imaginary > 500) // Check this case before continuing.
    {
        std::cerr << "Complex components are out of the supported range\n";
        return 1; // Return the result for this branch.
    }
    int real_result = 0; // Update the intermediate value.
    int imaginary_result = 0;
    add_complex_values(first_real, first_imaginary, second_real, second_imaginary, real_result, imaginary_result);
    std::cout << "Prime: " << is_prime_number(prime_candidate) << '\n'; // Display the calculated result.
    std::cout << "Fibonacci value: " << bounded_fibonacci(fibonacci_index) << '\n';
    std::cout << "Complex sum: " << real_result << " + (" << imaginary_result << ")i\n";
    return 0; // Return the result for this branch.
}
