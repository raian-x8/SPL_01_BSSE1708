#include <iostream>
#include <sstream>
#include <string>

#include "../src/json_export.hpp"

bool matchesJsonString(
    const std::string &input,
    const std::string &expected)
{
    std::ostringstream output;

    writeJsonString(output, input);

    return output.str() == expected;
}

int main()
{
    const bool plainPassed =
        matchesJsonString(
            "student01",
            "\"student01\"");

    const bool quotePassed =
        matchesJsonString(
            "He said \"review\"",
            "\"He said \\\"review\\\"\"");

    const bool backslashPassed =
        matchesJsonString(
            "C:\\Users\\raian",
            "\"C:\\\\Users\\\\raian\"");

    const bool newlinePassed =
        matchesJsonString(
            "First\nSecond",
            "\"First\\nSecond\"");

    const bool controlPassed =
        matchesJsonString(
            std::string(1, '\x01'),
            "\"\\u0001\"");

    const bool emptyPassed =
        matchesJsonString(
            "",
            "\"\"");

    std::cout << "Plain JSON string: "
              << (plainPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Quotation mark escaping: "
              << (quotePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Backslash escaping: "
              << (backslashPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Newline escaping: "
              << (newlinePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Control character escaping: "
              << (controlPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty JSON string: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (plainPassed &&
            quotePassed &&
            backslashPassed &&
            newlinePassed &&
            controlPassed &&
            emptyPassed)
               ? 0
               : 1;
}