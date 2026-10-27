
#include "../src/code_region.hpp"
#include <cassert>
#include <iostream>
#include "../src/tokenizer.hpp"

int main()
{
    CodeRegion region{4, 9};

    assert(region.beginTokenIndex == 4);
    assert(region.endTokenIndex == 9);
    assert(region.endTokenIndex - region.beginTokenIndex == 5);

    std::vector<Token> tokens = tokenize("int main() { return 0; }");

    assert(tokens.size() == 9);

    CodeRegion body{4, tokens.size()};

    assert(body.endTokenIndex - body.beginTokenIndex == 5);
    assert(tokens[body.beginTokenIndex].lexeme == "{");
    assert(tokens[body.endTokenIndex - 1].lexeme == "}");

    std::vector<CodeRegion> regions = findBraceRegions(tokens);

    assert(regions.size() == 1);
    assert(regions[0].beginTokenIndex == 4);
    assert(regions[0].endTokenIndex == 9);

    std::vector<Token> nestedTokens = tokenize(
        "int main() { if (1) { return 1; } return 0; }");

    std::vector<CodeRegion> nestedRegions = findBraceRegions(nestedTokens);

    assert(nestedTokens.size() == 18);
    assert(nestedRegions.size() == 2);

    assert(nestedRegions[0].beginTokenIndex == 9);
    assert(nestedRegions[0].endTokenIndex == 14);

    assert(nestedRegions[1].beginTokenIndex == 4);
    assert(nestedRegions[1].endTokenIndex == 18);

    std::vector<Token> noBraceTokens = tokenize("int x = 10;");

    std::vector<CodeRegion> noBraceRegions =
        findBraceRegions(noBraceTokens);

    assert(noBraceRegions.empty());

    std::vector<Token> unmatchedTokens = tokenize("int main() {");

    std::vector<CodeRegion> unmatchedRegions =
        findBraceRegions(unmatchedTokens);

    assert(unmatchedRegions.empty());

    std::vector<Token> closingTokens = tokenize("}");

    std::vector<CodeRegion> closingRegions =
        findBraceRegions(closingTokens);

    assert(closingRegions.empty());

    std::vector<Token> emptyBlockTokens = tokenize("{}");

    std::vector<CodeRegion> emptyBlockRegions =
        findBraceRegions(emptyBlockTokens);

    assert(emptyBlockRegions.size() == 1);
    assert(emptyBlockRegions[0].beginTokenIndex == 0);
    assert(emptyBlockRegions[0].endTokenIndex == 2);

    std::cout << "Code region smoke test passed.\n";

    return 0;
}
