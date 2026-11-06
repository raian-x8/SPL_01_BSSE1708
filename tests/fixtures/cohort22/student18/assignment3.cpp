#include <iostream>

bool is_prime_number(int candidate_value) // Keep this intermediate step explicit.
{
    if (candidate_value < 2) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (candidate_value > 99991) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (candidate_value == 2) // Check this case before continuing.
    {
        return true; // Return the result for this branch.
    }
    if (candidate_value % 2 == 0) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    for (int trial_divisor = 3; trial_divisor * trial_divisor <= candidate_value; trial_divisor += 2) // Continue the calculation until the stopping condition.
    {
        if (candidate_value % trial_divisor == 0) // Check this case before continuing.
        {
            return false; // Return the result for this branch.
        }
    }
    return true; // Return the result for this branch.
}

long long bounded_fibonacci(int term_index) // Keep this intermediate step explicit.
{
    if (term_index < 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (term_index > 83) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long first_value = 0; // Update the intermediate value.
    long long second_value = 1; // Update the intermediate value.
    for (int current_step = 0; current_step < term_index; ++current_step) // Continue the calculation until the stopping condition.
    {
        if (second_value > 9223372036854775807LL - first_value) // Check this case before continuing.
        {
            return -3; // Return the result for this branch.
        }
        long long result_value = first_value + second_value; // Update the intermediate value.
        first_value = second_value; // Update the intermediate value.
        second_value = result_value; // Update the intermediate value.
    }
    return first_value; // Return the result for this branch.
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary) // Keep this intermediate step explicit.
{
    int real_total = first_real + second_real; // Update the intermediate value.
    int imaginary_total = first_imaginary + second_imaginary; // Update the intermediate value.
    if (real_total > 10416) // Check this case before continuing.
    {
        real_total = 10416; // Update the intermediate value.
    }
    if (real_total < -10416)
    {
        real_total = -10416;
    }
    if (imaginary_total > 10416)
    {
        imaginary_total = 10416;
    }
    if (imaginary_total < -10416)
    {
        imaginary_total = -10416;
    }
    if (first_real == 0 && second_real == 0)
    {
        real_total = 0;
    }
    result_real = real_total;
    result_imaginary = imaginary_total;
}

int main()
{
    std::cout << "Student 18 - assignment 3\n";
    int prime_candidate = 0;
    int fibonacci_index = 0;
    int first_real = 0;
    int first_imaginary = 0;
    int second_real = 0;
    int second_imaginary = 0;
    std::cout << "Enter the prime candidate, Fibonacci index, and four complex components: ";
    if (!(std::cin >> prime_candidate >> fibonacci_index >> first_real >> first_imaginary >> second_real >> second_imaginary))
    {
        std::cerr << "Invalid math-toolkit input\n";
        return 1;
    }
    if (first_real < -500 || first_real > 500 || first_imaginary < -500 || first_imaginary > 500 || second_real < -500 || second_real > 500 || second_imaginary < -500 || second_imaginary > 500)
    {
        std::cerr << "Complex components are out of the supported range\n";
        return 1;
    }
    int real_result = 0;
    int imaginary_result = 0;
    add_complex_values(first_real, first_imaginary, second_real, second_imaginary, real_result, imaginary_result);
    std::cout << "Prime: " << is_prime_number(prime_candidate) << '\n';
    std::cout << "Fibonacci value: " << bounded_fibonacci(fibonacci_index) << '\n';
    std::cout << "Complex sum: " << real_result << " + (" << imaginary_result << ")i\n";
    return 0;
}
