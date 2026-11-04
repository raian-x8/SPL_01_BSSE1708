#include <iostream>
#include <string>

#include "../src/source_statistics.hpp"

bool checkLineCounts(
    const std::string &testName,
    const std::string &source,
    std::size_t expectedLines,
    std::size_t expectedBlankLines)
{
    const SourceStatistics result =
        calculateSourceStatistics(source, 0, 0);

    const bool passed =
        result.totalLines == expectedLines &&
        result.blankLines == expectedBlankLines;

    std::cout << testName << ": "
              << (passed ? "PASS" : "FAIL") << '\n';

    return passed;
}

int main()
{
    const bool empty = checkLineCounts(
        "Empty file", "", 0, 0);

    const bool single = checkLineCounts(
        "Single line", "int x = 1;", 1, 0);

    const bool trailing = checkLineCounts(
        "Trailing newline", "int x = 1;\n", 1, 0);

    const bool whitespace = checkLineCounts(
        "Whitespace-only line",
        "int x = 1;\n \t \nreturn x;", 3, 1);

    const bool windows = checkLineCounts(
        "Windows CRLF",
        "int x = 1;\r\n\r\nreturn x;\r\n", 3, 1);

    const SourceStatistics counts =
        calculateSourceStatistics("int x = 1;", 7, 2);

    const bool suppliedCounts =
        counts.tokenCount == 7 &&
        counts.recognizedFunctionBodies == 2;

    std::cout << "Supplied counts: "
              << (suppliedCounts ? "PASS" : "FAIL") << '\n';

    // Verify aggregation across two source files.
    AggregateStatistics aggregate;

    const SourceStatistics firstSource{10, 2, 20, 1};
    const SourceStatistics secondSource{15, 3, 30, 2};

    accumulateSourceStatistics(aggregate, firstSource);
    accumulateSourceStatistics(aggregate, secondSource);

    const bool aggregateTotals =
        aggregate.fileCount == 2 &&
        aggregate.totalLines == 25 &&
        aggregate.blankLines == 5 &&
        aggregate.totalTokens == 50 &&
        aggregate.totalRecognizedFunctionBodies == 3;

    std::cout << "Two-file aggregation: "
              << (aggregateTotals ? "PASS" : "FAIL") << '\n';

    return (empty && single && trailing &&
            whitespace && windows && suppliedCounts)
               ? 0
               : 1;
}