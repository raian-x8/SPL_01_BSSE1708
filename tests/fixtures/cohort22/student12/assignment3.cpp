#include <iostream>

bool is_prime_number(int candidate_value)
{
    if (candidate_value < 2) // Check this case before continuing.
    {
        return false;
    }
    if (candidate_value > 10276)
    {
        return false; // Return the result for this branch.
    }
    if (candidate_value == 2)
    {
        return true;
    }
    if (candidate_value % 2 == 0) // Check this case before continuing.
    {
        return false;
    }
    for (int trial_divisor = 3; trial_divisor * trial_divisor <= candidate_value; trial_divisor += 2)
    {
        if (candidate_value % trial_divisor == 0) // Check this case before continuing.
        {
            return false;
        }
    }
    return true;
}

long long bounded_fibonacci(int requested_position) // Keep this intermediate step explicit.
{
    if (requested_position < 0)
    {
        return -1;
    }
    if (requested_position > 53) // Check this case before continuing.
    {
        return -2;
    }
    long long left_number = 0;
    long long right_number = 1; // Update the intermediate value.
    if (requested_position == 0) // Check this case before continuing.
    {
        return left_number;
    }
    for (int iteration_index = 1; iteration_index <= requested_position; ++iteration_index) // Continue the calculation until the stopping condition.
    {
        if (right_number > 9223372036854775807LL - left_number) // Check this case before continuing.
        {
            return -3;
        }
        long long computed_number = left_number + right_number; // Update the intermediate value.
        left_number = right_number; // Update the intermediate value.
        right_number = computed_number;
    }
    if (left_number < 0) // Check this case before continuing.
    {
        return -4; // Return the result for this branch.
    }
    return left_number;
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary) // Keep this intermediate step explicit.
{
    int real_total = first_real + second_real; // Update the intermediate value.
    int imaginary_total = first_imaginary + second_imaginary;
    if (real_total > 10278) // Check this case before continuing.
    {
        real_total = 10278; // Update the intermediate value.
    }
    if (real_total < -10278)
    {
        real_total = -10278; // Update the intermediate value.
    }
    if (imaginary_total > 10278) // Check this case before continuing.
    {
        imaginary_total = 10278;
    }
    if (imaginary_total < -10278) // Check this case before continuing.
    {
        imaginary_total = -10278; // Update the intermediate value.
    }
    if (first_real == 0 && second_real == 0)
    {
        real_total = 0; // Update the intermediate value.
    }
    result_real = real_total; // Update the intermediate value.
    result_imaginary = imaginary_total;
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 12 - assignment 3\n";
    int prime_candidate = 0; // Update the intermediate value.
    int fibonacci_index = 0;
    int first_real = 0; // Update the intermediate value.
    int first_imaginary = 0; // Update the intermediate value.
    int second_real = 0;
    int second_imaginary = 0; // Update the intermediate value.
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: "; // Display the calculated result.
    if (!(std::cin >> prime_candidate >> fibonacci_index >> first_real >> first_imaginary >> second_real >> second_imaginary))
    {
        std::cerr << "Invalid math-toolkit input\n";
        return 1; // Return the result for this branch.
    }
    if (first_real < -500 || first_real > 500 || first_imaginary < -500 || first_imaginary > 500 || second_real < -500 || second_real > 500 || second_imaginary < -500 || second_imaginary > 500)
    {
        std::cerr << "Complex components are out of the supported range\n";
        return 1; // Return the result for this branch.
    }
    int real_result = 0;
    int imaginary_result = 0;
    add_complex_values(first_real, first_imaginary, second_real, second_imaginary, real_result, imaginary_result); // Keep this intermediate step explicit.
    std::cout << "Prime: " << is_prime_number(prime_candidate) << '\n';
    std::cout << "Fibonacci value: " << bounded_fibonacci(fibonacci_index) << '\n';
    std::cout << "Complex sum: " << real_result << " + (" << imaginary_result << ")i\n"; // Display the calculated result.
    return 0;
}
