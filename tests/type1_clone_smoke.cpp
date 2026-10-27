
#include "../src/type1_clone.hpp"
#include "../src/function_region.hpp"
#include "../src/tokenizer.hpp"
#include "../src/preprocessor.hpp"

#include <cassert>
#include <iostream>

int main()
{
    std::vector<Token> firstTokens = tokenize(
        "int add(int a, int b) { return a + b; }");

    std::vector<Token> sameTokens = tokenize(
        removeComments(
            "int add(int a,int b)\n"
            "{\n"
            "    // Calculate sum\n"
            "    return a+b;\n"
            "}"));

    std::vector<Token> differentTokens = tokenize(
        "int add(int a, int b) { return a - b; }");

    std::vector<CodeRegion> firstRegions =
        findFunctionBodyRegions(firstTokens);

    std::vector<CodeRegion> sameRegions =
        findFunctionBodyRegions(sameTokens);

    std::vector<CodeRegion> differentRegions =
        findFunctionBodyRegions(differentTokens);

    assert(firstRegions.size() == 1);
    assert(sameRegions.size() == 1);
    assert(differentRegions.size() == 1);

    assert(areType1BodyCandidates(
        firstTokens, firstRegions[0],
        sameTokens, sameRegions[0]));

    assert(!areType1BodyCandidates(
        firstTokens, firstRegions[0],
        differentTokens, differentRegions[0]));

    CodeRegion invalidRegion{0, firstTokens.size() + 1};

    assert(!areType1BodyCandidates(
        firstTokens, invalidRegion,
        sameTokens, sameRegions[0]));

    CodeRegion emptyRegion{
        firstRegions[0].beginTokenIndex,
        firstRegions[0].beginTokenIndex};

    assert(!areType1BodyCandidates(
        firstTokens, emptyRegion,
        sameTokens, sameRegions[0]));

    std::vector<Token> renamedTokens = tokenize(
        "int add(int x, int y) { return x + y; }");

    std::vector<CodeRegion> renamedRegions =
        findFunctionBodyRegions(renamedTokens);

    assert(renamedRegions.size() == 1);

    assert(!areType1BodyCandidates(
        firstTokens, firstRegions[0],
        renamedTokens, renamedRegions[0]));

    std::vector<Token> literalOriginalTokens = tokenize(
        "int value() { return 10; }");

    std::vector<Token> literalChangedTokens = tokenize(
        "int value() { return 20; }");

    std::vector<CodeRegion> literalOriginalRegions =
        findFunctionBodyRegions(literalOriginalTokens);

    std::vector<CodeRegion> literalChangedRegions =
        findFunctionBodyRegions(literalChangedTokens);

    assert(literalOriginalRegions.size() == 1);
    assert(literalChangedRegions.size() == 1);

    assert(!areType1BodyCandidates(
        literalOriginalTokens, literalOriginalRegions[0],
        literalChangedTokens, literalChangedRegions[0]));

    std::cout << "Type-1 clone smoke test passed.\n";

    return 0;
}
