
#include "../src/function_region.hpp"
#include "../src/tokenizer.hpp"

#include <cassert>
#include <iostream>

int main()
{
    std::vector<Token> tokens = tokenize(
        "int calculate(int x) { if (x > 0) { return x; } return 0; }");

    std::vector<CodeRegion> braceRegions = findBraceRegions(tokens);

    assert(braceRegions.size() == 2);

    std::vector<CodeRegion> functionRegions =
        findFunctionBodyRegions(tokens);

    assert(functionRegions.size() == 1);

    assert(functionRegions[0].beginTokenIndex == 6);
    assert(functionRegions[0].endTokenIndex == tokens.size());

    std::vector<Token> multipleTokens = tokenize(
        "int first() { return 1; } "
        "int second() { while (0) { return 2; } return 3; }");

    std::vector<CodeRegion> multipleBraceRegions =
        findBraceRegions(multipleTokens);

    assert(multipleBraceRegions.size() == 3);

    std::vector<CodeRegion> multipleFunctionRegions =
        findFunctionBodyRegions(multipleTokens);

    assert(multipleFunctionRegions.size() == 2);

    assert(multipleFunctionRegions[0].beginTokenIndex == 4);
    assert(multipleFunctionRegions[0].endTokenIndex == 9);

    assert(multipleFunctionRegions[1].beginTokenIndex == 13);
    assert(multipleFunctionRegions[1].endTokenIndex == 27);

    std::vector<Token> lambdaTokens = tokenize(
        "auto square = [](int x) { return x * x; };");

    std::vector<CodeRegion> lambdaBraceRegions =
        findBraceRegions(lambdaTokens);

    assert(lambdaBraceRegions.size() == 1);

    std::vector<CodeRegion> lambdaFunctionRegions =
        findFunctionBodyRegions(lambdaTokens);

    assert(lambdaFunctionRegions.empty());

    std::vector<Token> namespaceTokens = tokenize(
        "namespace Demo { int read() { return 1; } }");

    std::vector<CodeRegion> namespaceBraceRegions =
        findBraceRegions(namespaceTokens);

    assert(namespaceBraceRegions.size() == 2);

    std::vector<CodeRegion> namespaceFunctionRegions =
        findFunctionBodyRegions(namespaceTokens);

    assert(namespaceFunctionRegions.size() == 1);

    assert(namespaceFunctionRegions[0].beginTokenIndex == 7);
    assert(namespaceFunctionRegions[0].endTokenIndex == 12);

    std::vector<Token> initializerTokens = tokenize(
        "int setup() { int values[] = {1, 2}; return 0; }");

    std::vector<CodeRegion> initializerBraceRegions =
        findBraceRegions(initializerTokens);

    assert(initializerBraceRegions.size() == 2);

    assert(initializerBraceRegions[0].beginTokenIndex == 10);
    assert(initializerBraceRegions[0].endTokenIndex == 15);

    std::vector<CodeRegion> initializerFunctionRegions =
        findFunctionBodyRegions(initializerTokens);

    assert(initializerFunctionRegions.size() == 1);
    assert(initializerFunctionRegions[0].beginTokenIndex == 4);
    assert(initializerFunctionRegions[0].endTokenIndex == initializerTokens.size());

    std::cout << "Function region smoke test passed.\n";

    return 0;
}
