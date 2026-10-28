#include <iostream>
#include <string>
#include "../src/tokenizer.hpp"
#include "../src/type2_clone.hpp"

bool compareBodyText(
    const std::string &firstBody,
    const std::string &secondBody)
{
    const std::vector<Token> firstTokens = tokenize(firstBody);
    const std::vector<Token> secondTokens = tokenize(secondBody);

    const CodeRegion firstRegion{0, firstTokens.size()};
    const CodeRegion secondRegion{0, secondTokens.size()};

    return areType2BodyCandidates(
        firstTokens, firstRegion,
        secondTokens, secondRegion);
}

int main()
{
    bool positive = compareBodyText(
        "int sum = a + b; return sum;",
        "int total = x + y; return total;");

    bool negative = compareBodyText(
        "return a + a;",
        "return x + y;");

    bool reverseCollision = compareBodyText(
        "return a + b;",
        "return x + x;");

    bool exactType1 = compareBodyText(
        "return a + a;",
        "return a + a;");

    bool changedOperator = compareBodyText(
        "return a + b;",
        "return x - y;");

    bool changedLiteral = compareBodyText(
        "return a + 1;",
        "return x + 2;");

    const std::vector<Token> boundaryFirstTokens =
        tokenize("return a + b;");

    const std::vector<Token> boundarySecondTokens =
        tokenize("return x + y;");

    const CodeRegion validFirstRegion{
        0, boundaryFirstTokens.size()};

    const CodeRegion validSecondRegion{
        0, boundarySecondTokens.size()};

    const CodeRegion emptyRegion{0, 0};

    const CodeRegion outOfBoundsRegion{
        0, boundaryFirstTokens.size() + 1};

    bool validBoundary = areType2BodyCandidates(
        boundaryFirstTokens, validFirstRegion,
        boundarySecondTokens, validSecondRegion);

    bool emptyBoundary = areType2BodyCandidates(
        boundaryFirstTokens, emptyRegion,
        boundarySecondTokens, validSecondRegion);

    bool outOfBoundsBoundary = areType2BodyCandidates(
        boundaryFirstTokens, outOfBoundsRegion,
        boundarySecondTokens, validSecondRegion);

    const std::vector<Token> multiFirstTokens =
        tokenize("return a + b; return a + a;");

    const std::vector<Token> multiSecondTokens =
        tokenize("return x + y; return a + a;");

    const std::size_t firstSplit =
        tokenize("return a + b;").size();

    const std::size_t secondSplit =
        tokenize("return x + y;").size();

    const std::vector<CodeRegion> multiFirstRegions{
        {0, firstSplit},
        {firstSplit, multiFirstTokens.size()}};

    const std::vector<CodeRegion> multiSecondRegions{
        {0, secondSplit},
        {secondSplit, multiSecondTokens.size()}};

    const std::vector<Type2BodyMatch> multiMatches =
        findType2BodyMatches(
            multiFirstTokens, multiFirstRegions,
            multiSecondTokens, multiSecondRegions);

    bool multiRegionDiscovery =
        multiMatches.size() == 1 &&
        multiMatches[0].firstRegion.beginTokenIndex == 0 &&
        multiMatches[0].secondRegion.beginTokenIndex == 0;

    std::cout << "Consistent renaming: "
              << (positive ? "PASS" : "FAIL") << '\n';

    std::cout << "Inconsistent renaming rejected: "
              << (!negative ? "PASS" : "FAIL") << '\n';

    std::cout << "Reverse collision rejected: "
              << (!reverseCollision ? "PASS" : "FAIL") << '\n';

    std::cout << "Exact Type-1 excluded: "
              << (!exactType1 ? "PASS" : "FAIL") << '\n';

    std::cout << "Changed operator rejected: "
              << (!changedOperator ? "PASS" : "FAIL") << '\n';

    std::cout << "Changed literal rejected: "
              << (!changedLiteral ? "PASS" : "FAIL") << '\n';

    std::cout << "Valid region accepted: "
              << (validBoundary ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty region rejected: "
              << (!emptyBoundary ? "PASS" : "FAIL") << '\n';

    std::cout << "Out-of-bounds region rejected: "
              << (!outOfBoundsBoundary ? "PASS" : "FAIL") << '\n';

    std::cout << "Multi-region discovery: "
              << (multiRegionDiscovery ? "PASS" : "FAIL") << '\n';

    return (positive && !negative &&
            !reverseCollision && !exactType1 &&
            !changedOperator && !changedLiteral &&
            validBoundary && !emptyBoundary &&
            !outOfBoundsBoundary &&
            multiRegionDiscovery)
               ? 0
               : 1;
}