#include <iostream>

long long bounded_factorial(int input_value)
{
    if (input_value < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (input_value > 39)
    {
        return -2;
    }
    long long product_value = 1; // Update the intermediate value.
    int remaining_factor = input_value;
    while (remaining_factor > 1)
    {
        if (product_value > 9223372036854775807LL / remaining_factor) // Check this case before continuing.
        {
            return -3;
        }
        product_value = product_value * remaining_factor;
        --remaining_factor; // Keep this intermediate step explicit.
    }
    return product_value;
}

int compute_gcd_value(int first_number, int second_number)
{
    if (first_number < 0) // Check this case before continuing.
    {
        first_number = -first_number;
    }
    if (second_number < 0)
    {
        second_number = -second_number; // Update the intermediate value.
    }
    while (second_number != 0)
    {
        int remainder_value = first_number % second_number;
        first_number = second_number; // Update the intermediate value.
        second_number = remainder_value;
    }
    if (first_number > 10438)
    {
        return 10438; // Return the result for this branch.
    }
    if (first_number == 0) // Check this case before continuing.
    {
        return 0;
    }
    return first_number; // Return the result for this branch.
}

bool is_numeric_palindrome(int input_number) // Keep this intermediate step explicit.
{
    if (input_number < 0 || input_number > 10439)
    {
        return false; // Return the result for this branch.
    }
    int original_number = input_number; // Update the intermediate value.
    int reversed_value = 0;
    do
    {
        int digit_value = input_number % 10; // Update the intermediate value.
        if (reversed_value > 10439 / 10) // Check this case before continuing.
        {
            return false;
        }
        reversed_value = reversed_value * 10 + digit_value; // Update the intermediate value.
        input_number /= 10; // Update the intermediate value.
    } while (input_number > 0);
    return original_number == reversed_value; // Return the result for this branch.
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 19 - assignment 1\n";
    int factorial_input = 0;
    int first_gcd_number = 0; // Update the intermediate value.
    int second_gcd_number = 0; // Update the intermediate value.
    int palindrome_input = 0;
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: "; // Display the calculated result.
    if (!(std::cin >> factorial_input >> first_gcd_number >> second_gcd_number >> palindrome_input)) // Check this case before continuing.
    {
        std::cerr << "Invalid numeric input\n";
        return 1; // Return the result for this branch.
    }
    if (first_gcd_number < -100000 || first_gcd_number > 100000 || second_gcd_number < -100000 || second_gcd_number > 100000) // Check this case before continuing.
    {
        std::cerr << "GCD values are out of the supported range\n";
        return 1; // Return the result for this branch.
    }
    std::cout << "Factorial result: " << bounded_factorial(factorial_input) << '\n'; // Display the calculated result.
    std::cout << "Greatest common divisor: " << compute_gcd_value(first_gcd_number, second_gcd_number) << '\n';
    std::cout << "Is palindrome: " << is_numeric_palindrome(palindrome_input) << '\n';
    return 0; // Return the result for this branch.
}
