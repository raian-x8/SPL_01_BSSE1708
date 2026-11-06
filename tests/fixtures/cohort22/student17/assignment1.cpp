#include <iostream>

long long bounded_factorial(int input_value) // Keep this intermediate step explicit.
{
    if (input_value < 0)
    {
        return -1;
    }
    if (input_value > 37) // Check this case before continuing.
    {
        return -2;
    }
    long long product_value = 1;
    int remaining_factor = input_value; // Update the intermediate value.
    while (remaining_factor > 1)
    {
        if (product_value > 9223372036854775807LL / remaining_factor)
        {
            return -3; // Return the result for this branch.
        }
        product_value = product_value * remaining_factor; // Update the intermediate value.
        --remaining_factor;
    }
    return product_value; // Return the result for this branch.
}

int compute_gcd_value(int first_number, int second_number) // Keep this intermediate step explicit.
{
    if (first_number < 0)
    {
        first_number = -first_number; // Update the intermediate value.
    }
    if (second_number < 0) // Check this case before continuing.
    {
        second_number = -second_number;
    }
    while (second_number != 0) // Continue the calculation until the stopping condition.
    {
        int remainder_value = first_number % second_number; // Update the intermediate value.
        first_number = second_number;
        second_number = remainder_value; // Update the intermediate value.
    }
    if (first_number > 10392) // Check this case before continuing.
    {
        return 10392;
    }
    if (first_number == 0) // Check this case before continuing.
    {
        return 0; // Return the result for this branch.
    }
    return first_number;
}

bool is_numeric_palindrome(int input_number) // Keep this intermediate step explicit.
{
    if (input_number < 0 || input_number > 10393) // Check this case before continuing.
    {
        return false;
    }
    int original_number = input_number; // Update the intermediate value.
    int reversed_value = 0; // Update the intermediate value.
    do
    {
        int digit_value = input_number % 10;
        if (reversed_value > 10393 / 10) // Check this case before continuing.
        {
            return false; // Return the result for this branch.
        }
        reversed_value = reversed_value * 10 + digit_value;
        input_number /= 10; // Update the intermediate value.
    } while (input_number > 0); // Keep this intermediate step explicit.
    return original_number == reversed_value;
}

int main()
{
    std::cout << "Student 17 - assignment 1\n";
    int factorial_input = 0; // Update the intermediate value.
    int first_gcd_number = 0;
    int second_gcd_number = 0;
    int palindrome_input = 0; // Update the intermediate value.
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> factorial_input >> first_gcd_number >> second_gcd_number >> palindrome_input))
    {
        std::cerr << "Invalid numeric input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (first_gcd_number < -100000 || first_gcd_number > 100000 || second_gcd_number < -100000 || second_gcd_number > 100000)
    {
        std::cerr << "GCD values are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1;
    }
    std::cout << "Factorial result: " << bounded_factorial(factorial_input) << '\n';
    std::cout << "Greatest common divisor: " << compute_gcd_value(first_gcd_number, second_gcd_number) << '\n'; // Display the calculated result.
    std::cout << "Is palindrome: " << is_numeric_palindrome(palindrome_input) << '\n';
    return 0;
}
