
#include <iostream>
#include <string>
#include "../src/preprocessor.hpp"

int main()
{

    std::string input = "int x = 10; // note\nint y = 20;\n";
    std::string expected = "int x = 10;        \nint y = 20;\n";

    // Test 1: Single-line comments
    if (removeComments(input) != expected)
    {
        std::cout << "FAIL: Single-line comment removal\n";
        return 1;
    }

    std::cout << "PASS: Single-line comment removal\n";

    // Test 2: Block comments
    std::string blockInput = "int a=1;/*x*/int b=2;\n";
    std::string blockExpected = "int a=1;     int b=2;\n";

    if (removeComments(blockInput) != blockExpected)
    {
        std::cout << "FAIL: Block-comment removal\n";
        return 1;
    }

    std::cout << "PASS: Block-comment removal\n";

    // Test 3: Preserve comment symbols inside strings
    std::string stringInput =
        "std::string url = \"https://example.com/*not a comment*/\";\n";

    if (removeComments(stringInput) != stringInput)
    {
        std::cout << "FAIL: String literal preservation\n";
        return 1;
    }

    std::cout << "PASS: String literal preservation\n";

    // Test 4: Preserve escaped quotes inside strings
    std::string escapedInput =
        "std::string message = \"He said: \\\"hello // still text\\\"\";\n";

    if (removeComments(escapedInput) != escapedInput)
    {
        std::cout << "FAIL: Escaped quote preservation\n";
        return 1;
    }

    std::cout << "PASS: Escaped quote preservation\n";

    // Test 5: Preserve character literals
    std::string charInput =
        "char quote = '\\''; char slash = '/';\n";

    if (removeComments(charInput) != charInput)
    {
        std::cout << "FAIL: Character literal preservation\n";
        return 1;
    }

    std::cout << "PASS: Character literal preservation\n";

    return 0;
}
