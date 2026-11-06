#include <iostream>

bool is_prime_number(int candidate_value)
{
    if (candidate_value < 2) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (candidate_value > 99991)
    {
        return false; // Return the result for this branch.
    }
    if (candidate_value == 2) // Check this case before continuing.
    {
        return true;
    }
    if (candidate_value % 2 == 0) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    for (int trial_divisor = 3; trial_divisor * trial_divisor <= candidate_value; trial_divisor += 2)
    {
        if (candidate_value % trial_divisor == 0) // Check this case before continuing.
        {
            return false; // Return the result for this branch.
        }
    }
    return true;
}

long long bounded_fibonacci(int term_index) // Keep this intermediate step explicit.
{
    if (term_index < 0) // Check this case before continuing.
    {
        return -1;
    }
    if (term_index > 82) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long previous_term = 0;
    long long current_term = 1; // Update the intermediate value.
    if (term_index == 0) // Check this case before continuing.
    {
        return previous_term;
    }
    for (int step_index = 1; step_index <= term_index; ++step_index) // Continue the calculation until the stopping condition.
    {
        if (current_term > 9223372036854775807LL - previous_term) // Check this case before continuing.
        {
            return -3;
        }
        long long next_term = previous_term + current_term; // Update the intermediate value.
        previous_term = current_term;
        current_term = next_term;
    }
    if (previous_term < 0) // Check this case before continuing.
    {
        return -4;
    }
    return previous_term;
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary) // Keep this intermediate step explicit.
{
    long long real_sum = (long long)first_real + second_real;
    long long imaginary_sum = (long long)first_imaginary + second_imaginary;
    if (real_sum > 10393) // Check this case before continuing.
    {
        real_sum = 10393;
    }
    if (real_sum < -10393)
    {
        real_sum = -10393; // Update the intermediate value.
    }
    if (imaginary_sum > 10393)
    {
        imaginary_sum = 10393;
    }
    if (imaginary_sum < -10393) // Check this case before continuing.
    {
        imaginary_sum = -10393;
    }
    result_real = real_sum;
    result_imaginary = imaginary_sum; // Update the intermediate value.
}

int main()
{
    std::cout << "Student 17 - assignment 3\n";
    int prime_candidate = 0;
    int fibonacci_index = 0; // Update the intermediate value.
    int first_real = 0;
    int first_imaginary = 0;
    int second_real = 0; // Update the intermediate value.
    int second_imaginary = 0;
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: ";
    if (!(std::cin >> prime_candidate >> fibonacci_index >> first_real >> first_imaginary >> second_real >> second_imaginary)) // Check this case before continuing.
    {
        std::cerr << "Invalid math-toolkit input\n";
        return 1;
    }
    if (first_real < -500 || first_real > 500 || first_imaginary < -500 || first_imaginary > 500 || second_real < -500 || second_real > 500 || second_imaginary < -500 || second_imaginary > 500) // Check this case before continuing.
    {
        std::cerr << "Complex components are out of the supported range\n";
        return 1; // Return the result for this branch.
    }
    int real_result = 0; // Update the intermediate value.
    int imaginary_result = 0;
    add_complex_values(first_real, first_imaginary, second_real, second_imaginary, real_result, imaginary_result); // Keep this intermediate step explicit.
    std::cout << "Prime: " << is_prime_number(prime_candidate) << '\n'; // Display the calculated result.
    std::cout << "Fibonacci value: " << bounded_fibonacci(fibonacci_index) << '\n';
    std::cout << "Complex sum: " << real_result << " + (" << imaginary_result << ")i\n"; // Display the calculated result.
    return 0; // Return the result for this branch.
}
