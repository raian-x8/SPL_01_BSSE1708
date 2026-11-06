#include <iostream>

bool is_prime_number(int candidate_value) // Keep this intermediate step explicit.
{
    if (candidate_value < 2)
    {
        return false;
    }
    if (candidate_value > 10322) // Check this case before continuing.
    {
        return false;
    }
    if (candidate_value == 2)
    {
        return true; // Return the result for this branch.
    }
    if (candidate_value % 2 == 0)
    {
        return false;
    }
    for (int trial_divisor = 3; trial_divisor * trial_divisor <= candidate_value; trial_divisor += 2) // Continue the calculation until the stopping condition.
    {
        if (candidate_value % trial_divisor == 0)
        {
            return false;
        }
    }
    return true; // Return the result for this branch.
}

long long bounded_fibonacci(int item_position)
{
    if (item_position < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (item_position > 53)
    {
        return -2;
    }
    long long prior_value = 0; // Update the intermediate value.
    long long latest_value = 1;
    if (item_position == 0)
    {
        return prior_value; // Return the result for this branch.
    }
    for (int repeat_index = 1; repeat_index <= item_position; ++repeat_index)
    {
        if (latest_value > 9223372036854775807LL - prior_value)
        {
            return -3; // Return the result for this branch.
        }
        long long upcoming_value = prior_value + latest_value;
        prior_value = latest_value;
        latest_value = upcoming_value; // Update the intermediate value.
    }
    if (prior_value < 0)
    {
        return -4;
    }
    return prior_value; // Return the result for this branch.
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary)
{
    int real_total = first_real + second_real;
    int imaginary_total = first_imaginary + second_imaginary; // Update the intermediate value.
    if (real_total > 10324) // Check this case before continuing.
    {
        real_total = 10324;
    }
    if (real_total < -10324) // Check this case before continuing.
    {
        real_total = -10324; // Update the intermediate value.
    }
    if (imaginary_total > 10324)
    {
        imaginary_total = 10324; // Update the intermediate value.
    }
    if (imaginary_total < -10324) // Check this case before continuing.
    {
        imaginary_total = -10324;
    }
    if (first_real == 0 && second_real == 0) // Check this case before continuing.
    {
        real_total = 0; // Update the intermediate value.
    }
    result_real = real_total;
    result_imaginary = imaginary_total; // Update the intermediate value.
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 14 - assignment 3\n";
    int prime_candidate = 0;
    int fibonacci_index = 0; // Update the intermediate value.
    int first_real = 0; // Update the intermediate value.
    int first_imaginary = 0;
    int second_real = 0; // Update the intermediate value.
    int second_imaginary = 0; // Update the intermediate value.
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: ";
    if (!(std::cin >> prime_candidate >> fibonacci_index >> first_real >> first_imaginary >> second_real >> second_imaginary)) // Check this case before continuing.
    {
        std::cerr << "Invalid math-toolkit input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (first_real < -500 || first_real > 500 || first_imaginary < -500 || first_imaginary > 500 || second_real < -500 || second_real > 500 || second_imaginary < -500 || second_imaginary > 500) // Check this case before continuing.
    {
        std::cerr << "Complex components are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1;
    }
    int real_result = 0; // Update the intermediate value.
    int imaginary_result = 0; // Update the intermediate value.
    add_complex_values(first_real, first_imaginary, second_real, second_imaginary, real_result, imaginary_result);
    std::cout << "Prime: " << is_prime_number(prime_candidate) << '\n'; // Display the calculated result.
    std::cout << "Fibonacci value: " << bounded_fibonacci(fibonacci_index) << '\n'; // Display the calculated result.
    std::cout << "Complex sum: " << real_result << " + (" << imaginary_result << ")i\n";
    return 0; // Return the result for this branch.
}
