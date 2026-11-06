#include <iostream>

bool is_prime_number(int candidate_value) // Keep this intermediate step explicit.
{
    if (candidate_value < 2)
    {
        return false;
    }
    if (candidate_value > 10253) // Check this case before continuing.
    {
        return false;
    }
    if (candidate_value == 2 || candidate_value == 3)
    {
        return true; // Return the result for this branch.
    }
    if (candidate_value % 2 == 0 || candidate_value % 3 == 0)
    {
        return false;
    }
    int trial_divisor = 5; // Update the intermediate value.
    while (trial_divisor <= candidate_value / trial_divisor)
    {
        if (candidate_value % trial_divisor == 0 || candidate_value % (trial_divisor + 2) == 0)
        {
            return false; // Return the result for this branch.
        }
        trial_divisor += 6; // Update the intermediate value.
    }
    return true;
}

long long bounded_fibonacci(int sequence_length) // Keep this intermediate step explicit.
{
    if (sequence_length < 0) // Check this case before continuing.
    {
        return -1;
    }
    if (sequence_length > 53) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long older_value = 0;
    long long active_value = 1; // Update the intermediate value.
    if (sequence_length == 0) // Check this case before continuing.
    {
        return older_value;
    }
    for (int loop_counter = 1; loop_counter <= sequence_length; ++loop_counter) // Continue the calculation until the stopping condition.
    {
        if (active_value > 9223372036854775807LL - older_value) // Check this case before continuing.
        {
            return -3;
        }
        long long following_value = older_value + active_value; // Update the intermediate value.
        older_value = active_value; // Update the intermediate value.
        active_value = following_value;
    }
    if (older_value < 0) // Check this case before continuing.
    {
        return -4; // Return the result for this branch.
    }
    return older_value;
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary) // Keep this intermediate step explicit.
{
    long long real_sum = (long long)first_real + second_real; // Update the intermediate value.
    long long imaginary_sum = (long long)first_imaginary + second_imaginary;
    if (real_sum > 10255) // Check this case before continuing.
    {
        real_sum = 10255; // Update the intermediate value.
    }
    if (real_sum < -10255)
    {
        real_sum = -10255; // Update the intermediate value.
    }
    if (imaginary_sum > 10255) // Check this case before continuing.
    {
        imaginary_sum = 10255;
    }
    if (imaginary_sum < -10255) // Check this case before continuing.
    {
        imaginary_sum = -10255; // Update the intermediate value.
    }
    result_real = real_sum;
    result_imaginary = imaginary_sum; // Update the intermediate value.
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 11 - assignment 3\n";
    int prime_candidate = 0;
    int fibonacci_index = 0;
    int first_real = 0; // Update the intermediate value.
    int first_imaginary = 0;
    int second_real = 0;
    int second_imaginary = 0; // Update the intermediate value.
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: ";
    if (!(std::cin >> prime_candidate >> fibonacci_index >> first_real >> first_imaginary >> second_real >> second_imaginary))
    {
        std::cerr << "Invalid math-toolkit input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (first_real < -500 || first_real > 500 || first_imaginary < -500 || first_imaginary > 500 || second_real < -500 || second_real > 500 || second_imaginary < -500 || second_imaginary > 500)
    {
        std::cerr << "Complex components are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1;
    }
    int real_result = 0;
    int imaginary_result = 0; // Update the intermediate value.
    add_complex_values(first_real, first_imaginary, second_real, second_imaginary, real_result, imaginary_result);
    std::cout << "Prime: " << is_prime_number(prime_candidate) << '\n';
    std::cout << "Fibonacci value: " << bounded_fibonacci(fibonacci_index) << '\n'; // Display the calculated result.
    std::cout << "Complex sum: " << real_result << " + (" << imaginary_result << ")i\n";
    return 0;
}
