#include <iostream>

#include "../src/identifier_history.hpp"

// Create controlled identifier-style statistics for testing.
IdentifierStyleStatistics makeStyleStats(
    std::size_t camelCase,
    std::size_t pascalCase,
    std::size_t snakeCase)
{
    IdentifierStyleStatistics statistics;

    statistics.camelCase = camelCase;
    statistics.pascalCase = pascalCase;
    statistics.snakeCase = snakeCase;

    statistics.uniqueIdentifierCount =
        camelCase + pascalCase + snakeCase;

    return statistics;
}

int main()
{
    const IdentifierStyleStatistics camel =
        makeStyleStats(5, 0, 0);

    const IdentifierStyleStatistics snake =
        makeStyleStats(0, 0, 5);

    const IdentifierStyleStatistics fewIdentifiers =
        makeStyleStats(2, 0, 0);

    const IdentifierStyleStatistics mixedCurrent =
        makeStyleStats(2, 0, 3);

    // Test 1: Stable camelCase history followed by snake_case.
    const IdentifierHistoryResult changed =
        analyzeIdentifierHistory({camel, camel}, snake);

    const bool changedPassed =
        changed.sufficientData &&
        changed.stableHistoricalStyle &&
        changed.reviewRecommended &&
        changed.historicalDominantStyle == IdentifierStyle::CamelCase &&
        changed.currentDominantStyle == IdentifierStyle::SnakeCase;

    std::cout << "Historical style change: "
              << (changedPassed ? "PASS" : "FAIL") << '\n';

    // Test 2: Student consistently follows snake_case.
    const IdentifierHistoryResult consistent =
        analyzeIdentifierHistory({snake, snake}, snake);

    const bool consistentPassed =
        consistent.sufficientData &&
        consistent.stableHistoricalStyle &&
        !consistent.reviewRecommended &&
        consistent.historicalDominantStyle == IdentifierStyle::SnakeCase &&
        consistent.currentDominantStyle == IdentifierStyle::SnakeCase;

    std::cout << "Consistent student history: "
              << (consistentPassed ? "PASS" : "FAIL") << '\n';

    // Test 3: Only one historical submission exists.
    const IdentifierHistoryResult insufficientHistory =
        analyzeIdentifierHistory({camel}, snake);

    const bool historyPassed =
        !insufficientHistory.sufficientData &&
        !insufficientHistory.reviewRecommended;

    std::cout << "Single historical submission: "
              << (historyPassed ? "PASS" : "FAIL") << '\n';

    // Test 4: Historical submissions have different conventions.
    const IdentifierHistoryResult mixedHistory =
        analyzeIdentifierHistory({camel, snake}, snake);

    const bool mixedHistoryPassed =
        mixedHistory.sufficientData &&
        !mixedHistory.stableHistoricalStyle &&
        !mixedHistory.reviewRecommended;

    std::cout << "Mixed historical styles: "
              << (mixedHistoryPassed ? "PASS" : "FAIL") << '\n';

    // Test 5: A historical file has too few relevant identifiers.
    const IdentifierHistoryResult insufficientNames =
        analyzeIdentifierHistory({camel, fewIdentifiers}, snake);

    const bool namesPassed =
        !insufficientNames.sufficientData &&
        !insufficientNames.reviewRecommended;

    std::cout << "Insufficient identifiers: "
              << (namesPassed ? "PASS" : "FAIL") << '\n';

    // Test 6: Current submission has no clear dominant convention.
    const IdentifierHistoryResult unclearCurrent =
        analyzeIdentifierHistory({camel, camel}, mixedCurrent);

    const bool unclearPassed =
        unclearCurrent.sufficientData &&
        unclearCurrent.stableHistoricalStyle &&
        !unclearCurrent.reviewRecommended &&
        unclearCurrent.currentDominantStyle == IdentifierStyle::Other;

    std::cout << "No dominant current style: "
              << (unclearPassed ? "PASS" : "FAIL") << '\n';

    return (changedPassed &&
            consistentPassed &&
            historyPassed &&
            mixedHistoryPassed &&
            namesPassed &&
            unclearPassed)
               ? 0
               : 1;
}