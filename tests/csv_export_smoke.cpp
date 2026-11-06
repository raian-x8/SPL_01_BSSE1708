#include <iostream>
#include <string>

#include "../src/csv_export.hpp"

int main()
{
    // Test 1: Ordinary text should remain unchanged.
    const bool plainPassed =
        escapeCsvField("student01") == "student01";

    // Test 2: A comma requires surrounding quotation marks.
    const bool commaPassed =
        escapeCsvField("Hello, world") == "\"Hello, world\"";

    // Test 3: Internal quotation marks must be doubled.
    const bool quotePassed =
        escapeCsvField("He said \"review\"") ==
        "\"He said \"\"review\"\"\"";

    // Test 4: Newline characters require a quoted field.
    const bool newlinePassed =
        escapeCsvField("First\nSecond") ==
        "\"First\nSecond\"";

    // Test 5: Carriage returns require a quoted field.
    const bool carriageReturnPassed =
        escapeCsvField("First\rSecond") ==
        "\"First\rSecond\"";

    // Test 6: An empty field should remain empty.
    const bool emptyPassed =
        escapeCsvField("").empty();

    std::cout << "Ordinary text: "
              << (plainPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Comma escaping: "
              << (commaPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Quotation mark escaping: "
              << (quotePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Newline escaping: "
              << (newlinePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Carriage return escaping: "
              << (carriageReturnPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty field: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    const bool allPassed =
        plainPassed &&
        commaPassed &&
        quotePassed &&
        newlinePassed &&
        carriageReturnPassed &&
        emptyPassed;

    return allPassed ? 0 : 1;
}