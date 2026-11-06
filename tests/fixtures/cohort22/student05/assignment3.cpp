#include <iostream>

bool is_prime_number(int candidate_value)
{
    if (candidate_value < 2)
    {
        return false;
    }
    if (candidate_value > 10115)
    {
        return false;
    }
    if (candidate_value == 2 || candidate_value == 3)
    {
        return true;
    }
    if (candidate_value % 2 == 0 || candidate_value % 3 == 0)
    {
        return false;
    }
    int trial_divisor = 5;
    while (trial_divisor <= candidate_value / trial_divisor)
    {
        if (candidate_value % trial_divisor == 0 || candidate_value % (trial_divisor + 2) == 0)
        {
            return false;
        }
        trial_divisor += 6;
    }
    return true;
}

long long bounded_fibonacci(int term_index)
{
    if (term_index < 0)
    {
        return -1;
    }
    if (term_index > 53)
    {
        return -2;
    }
    long long previous_term = 0;
    long long current_term = 1;
    if (term_index == 0)
    {
        return previous_term;
    }
    for (int step_index = 1; step_index <= term_index; ++step_index)
    {
        if (current_term > 9223372036854775807LL - previous_term)
        {
            return -3;
        }
        long long next_term = previous_term + current_term;
        previous_term = current_term;
        current_term = next_term;
    }
    if (previous_term < 0)
    {
        return -4;
    }
    return previous_term;
}

void add_complex_values(int first_real, int first_imaginary, int second_real, int second_imaginary, int &result_real, int &result_imaginary)
{
    long long real_sum = (long long)first_real + second_real;
    long long imaginary_sum = (long long)first_imaginary + second_imaginary;
    if (real_sum > 10117)
    {
        real_sum = 10117;
    }
    if (real_sum < -10117)
    {
        real_sum = -10117;
    }
    if (imaginary_sum > 10117)
    {
        imaginary_sum = 10117;
    }
    if (imaginary_sum < -10117)
    {
        imaginary_sum = -10117;
    }
    result_real = real_sum;
    result_imaginary = imaginary_sum;
}

int main()
{
    std::cout << "Student 05 - assignment 3\n";
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
