#include <iostream>
#include <string>
#include <vector>

#include "../src/identifier_style.hpp"

struct StyleTestCase
{
    std::string identifier;
    IdentifierStyle expected;
};

int main()
{
    const StyleTestCase testCases[] = {
        {"calculateTotal", IdentifierStyle::CamelCase},
        {"StudentAverage", IdentifierStyle::PascalCase},
        {"total_sum", IdentifierStyle::SnakeCase},
        {"total", IdentifierStyle::Lowercase},
        {"x", IdentifierStyle::SingleLetter},
        {"_temp", IdentifierStyle::Other},
        {"total__sum", IdentifierStyle::Other},
        {"MAX_VALUE", IdentifierStyle::Other},
        {"", IdentifierStyle::Other}};

    bool allPassed = true;

    for (const StyleTestCase &test : testCases)
    {
        const IdentifierStyle actual =
            classifyIdentifierStyle(test.identifier);

        const bool passed = actual == test.expected;

        std::cout << (test.identifier.empty()
                          ? std::string("<empty>")
                          : test.identifier)
                  << ": "
                  << (passed ? "PASS" : "FAIL")
                  << '\n';

        if (!passed)
        {
            allPassed = false;
        }
    }

    // Verify counting of unique identifier names.
    const std::vector<Token> sampleTokens = {
        {TokenType::Keyword, "int", 1, 1},
        {TokenType::Identifier, "calculateTotal", 1, 5},
        {TokenType::Identifier, "firstNumber", 1, 20},
        {TokenType::Identifier, "secondNumber", 1, 38},
        {TokenType::Identifier, "total_sum", 2, 5},
        {TokenType::Identifier, "firstNumber", 2, 17},
        {TokenType::Identifier, "total_sum", 3, 12},
        {TokenType::Number, "42", 3, 20}};

    const IdentifierStyleStatistics statistics =
        calculateIdentifierStyleStatistics(sampleTokens);

    const bool correctStatistics =
        statistics.uniqueIdentifierCount == 4 &&
        statistics.totalIdentifierCharacters == 46 &&
        statistics.camelCase == 3 &&
        statistics.pascalCase == 0 &&
        statistics.snakeCase == 1 &&
        statistics.lowercase == 0 &&
        statistics.singleLetter == 0 &&
        statistics.other == 0;

    std::cout << "Unique identifier statistics: "
              << (correctStatistics ? "PASS" : "FAIL")
              << '\n';

    if (!correctStatistics)
    {
        allPassed = false;
    }

    // Verify that an empty token list is handled safely.
    const IdentifierStyleStatistics emptyStatistics =
        calculateIdentifierStyleStatistics({});

    const bool emptyStatisticsPassed =
        emptyStatistics.uniqueIdentifierCount == 0 &&
        emptyStatistics.totalIdentifierCharacters == 0 &&
        emptyStatistics.camelCase == 0 &&
        emptyStatistics.snakeCase == 0;

    std::cout << "Empty identifier list: "
              << (emptyStatisticsPassed ? "PASS" : "FAIL")
              << '\n';

    if (!emptyStatisticsPassed)
    {
        allPassed = false;
    }

    return allPassed ? 0 : 1;
}