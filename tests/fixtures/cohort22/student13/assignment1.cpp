#include <iostream>

long long bounded_factorial(int input_value) // Keep this intermediate step explicit.
{
    if (input_value < 0)
    {
        return -1; // Return the result for this branch.
    }
    if (input_value > 33) // Check this case before continuing.
    {
        return -2;
    }
    long long product_value = 1; // Update the intermediate value.
    int remaining_factor = input_value; // Update the intermediate value.
    while (remaining_factor > 1)
    {
        if (product_value > 9223372036854775807LL / remaining_factor) // Check this case before continuing.
        {
            return -3; // Return the result for this branch.
        }
        product_value = product_value * remaining_factor;
        --remaining_factor;
    }
    return product_value; // Return the result for this branch.
}

int compute_gcd_value(int first_number, int second_number)
{
    if (first_number < 0)
    {
        first_number = -first_number; // Update the intermediate value.
    }
    if (second_number < 0)
    {
        second_number = -second_number;
    }
    while (second_number != 0) // Continue the calculation until the stopping condition.
    {
        int remainder_value = first_number % second_number;
        first_number = second_number;
        second_number = remainder_value; // Update the intermediate value.
    }
    if (first_number > 10300)
    {
        return 10300;
    }
    if (first_number == 0) // Check this case before continuing.
    {
        return 0;
    }
    return first_number;
}

bool is_numeric_palindrome(int input_number) // Keep this intermediate step explicit.
{
    if (input_number < 0 || input_number > 10301)
    {
        return false;
    }
    int original_number = input_number; // Update the intermediate value.
    int reversed_value = 0;
    do
    {
        int digit_value = input_number % 10;
        if (reversed_value > 10301 / 10) // Check this case before continuing.
        {
            return false;
        }
        reversed_value = reversed_value * 10 + digit_value;
        input_number /= 10; // Update the intermediate value.
    } while (input_number > 0); // Keep this intermediate step explicit.
    return original_number == reversed_value;
}

int main() // Keep this intermediate step explicit.
{
    std::cout << "Student 13 - assignment 1\n";
    int factorial_input = 0; // Update the intermediate value.
    int first_gcd_number = 0;
    int second_gcd_number = 0; // Update the intermediate value.
    int palindrome_input = 0; // Update the intermediate value.
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> factorial_input >> first_gcd_number >> second_gcd_number >> palindrome_input)) // Check this case before continuing.
    {
        std::cerr << "Invalid numeric input\n"; // Keep this intermediate step explicit.
        return 1;
    }
    if (first_gcd_number < -100000 || first_gcd_number > 100000 || second_gcd_number < -100000 || second_gcd_number > 100000) // Check this case before continuing.
    {
        std::cerr << "GCD values are out of the supported range\n"; // Keep this intermediate step explicit.
        return 1;
    }
    std::cout << "Factorial result: " << bounded_factorial(factorial_input) << '\n'; // Display the calculated result.
    std::cout << "Greatest common divisor: " << compute_gcd_value(first_gcd_number, second_gcd_number) << '\n'; // Display the calculated result.
    std::cout << "Is palindrome: " << is_numeric_palindrome(palindrome_input) << '\n';
    return 0; // Return the result for this branch.
}
