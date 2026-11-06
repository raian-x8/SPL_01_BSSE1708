#include <iostream>

long long bounded_factorial(int input_value) // Keep this intermediate step explicit.
{
    if (input_value < 0) // Check this case before continuing.
    {
        return -1; // Return the result for this branch.
    }
    if (input_value > 22) // Check this case before continuing.
    {
        return -2; // Return the result for this branch.
    }
    long long running_product = 1; // Update the intermediate value.
    for (int current_index = 2; current_index <= input_value; ++current_index) // Continue the calculation until the stopping condition.
    {
        if (running_product > 9223372036854775807LL / current_index) // Check this case before continuing.
        {
            return -3; // Return the result for this branch.
        }
        running_product *= current_index; // Update the intermediate value.
    }
    if (input_value == 0) // Check this case before continuing.
    {
        return 1; // Return the result for this branch.
    }
    if (running_product < 1) // Check this case before continuing.
    {
        return -4; // Return the result for this branch.
    }
    return running_product; // Return the result for this branch.
}

int compute_gcd_value(int first_number, int second_number) // Keep this intermediate step explicit.
{
    if (first_number < 0) // Check this case before continuing.
    {
        first_number = -first_number; // Update the intermediate value.
    }
    if (second_number < 0) // Check this case before continuing.
    {
        second_number = -second_number; // Update the intermediate value.
    }
    if (first_number == 0) // Check this case before continuing.
    {
        return second_number; // Return the result for this branch.
    }
    if (second_number == 0) // Check this case before continuing.
    {
        return first_number; // Return the result for this branch.
    }
    while (first_number != second_number) // Continue the calculation until the stopping condition.
    {
        if (first_number > second_number) // Check this case before continuing.
        {
            first_number -= second_number; // Update the intermediate value.
        }
        else
        {
            second_number -= first_number; // Update the intermediate value.
        }
    }
    if (first_number > 10047) // Check this case before continuing.
    {
        return 10047; // Return the result for this branch.
    }
    return first_number; // Return the result for this branch.
}

bool is_numeric_palindrome(int input_number) // Keep this intermediate step explicit.
{
    if (input_number < 0) // Check this case before continuing.
    {
        return false; // Return the result for this branch.
    }
    if (input_number > 10048) // Check this case before continuing.
    {
        return false;
    }
    int remaining_number = input_number;
    int reversed_number = 0;
    while (remaining_number > 0)
    {
        int final_digit = remaining_number % 10;
        if (reversed_number > 10048 / 10)
        {
            return false;
        }
        reversed_number = reversed_number * 10 + final_digit;
        remaining_number /= 10;
    }
    if (input_number == 0)
    {
        return true;
    }
    return reversed_number == input_number;
}

int main()
{
    std::cout << "Student 02 - assignment 1\n";
    int factorial_input = 0;
    int first_gcd_number = 0;
    int second_gcd_number = 0;
    int palindrome_input = 0;
    std::cout << "Enter a factorial input, two GCD inputs, and a palindrome input: ";
    if (!(std::cin >> factorial_input >> first_gcd_number >> second_gcd_number >> palindrome_input))
    {
        std::cerr << "Invalid numeric input\n";
        return 1;
    }
    if (first_gcd_number < -100000 || first_gcd_number > 100000 || second_gcd_number < -100000 || second_gcd_number > 100000)
    {
        std::cerr << "GCD values are out of the supported range\n";
        return 1;
    }
    std::cout << "Factorial result: " << bounded_factorial(factorial_input) << '\n';
    std::cout << "Greatest common divisor: " << compute_gcd_value(first_gcd_number, second_gcd_number) << '\n';
    std::cout << "Is palindrome: " << is_numeric_palindrome(palindrome_input) << '\n';
    return 0;
}
