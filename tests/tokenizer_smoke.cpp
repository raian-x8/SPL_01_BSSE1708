#include "../src/tokenizer.hpp"

#include <cassert>
#include <iostream>

int main()
{
    // Test keyword classification, identifiers, and source positions.

    const std::vector<Token> tokens =
        tokenize("int total_2;\n_value");

    assert(tokens.size() == 4);

    assert(tokens[0].lexeme == "int");
    assert(tokens[0].type == TokenType::Keyword);
    assert(tokens[0].line == 1 && tokens[0].column == 1);

    assert(tokens[1].lexeme == "total_2");
    assert(tokens[1].type == TokenType::Identifier);
    assert(tokens[1].line == 1 && tokens[1].column == 5);

    // Verify punctuation recognition.
    assert(tokens[2].lexeme == ";");
    assert(tokens[2].type == TokenType::Punctuation);
    assert(tokens[2].line == 1 && tokens[2].column == 12);

    // Verify the identifier on the second line.
    assert(tokens[3].lexeme == "_value");
    assert(tokens[3].type == TokenType::Identifier);
    assert(tokens[3].line == 2 && tokens[3].column == 1);

    // Test decimal integer recognition across multiple lines.
    const std::vector<Token> numericTokens =
        tokenize("int x = 123;\nfloat y = 45;");

    assert(numericTokens.size() == 10);

    // Verify the first decimal integer.
    assert(numericTokens[3].lexeme == "123");
    assert(numericTokens[3].type == TokenType::Number);
    assert(numericTokens[3].line == 1 && numericTokens[3].column == 9);

    // Verify the second decimal integer.
    assert(numericTokens[8].lexeme == "45");
    assert(numericTokens[8].type == TokenType::Number);
    assert(numericTokens[8].line == 2 && numericTokens[8].column == 11);

    // Test basic floating-point literal recognition.
    const std::vector<Token> floatTokens =
        tokenize("double pi = 3.14;\nfloat rate = 0.5;");

    assert(floatTokens.size() == 10);

    // Verify the first floating-point literal.
    assert(floatTokens[3].lexeme == "3.14");
    assert(floatTokens[3].type == TokenType::Number);
    assert(floatTokens[3].line == 1 && floatTokens[3].column == 13);

    // Verify the second floating-point literal.
    assert(floatTokens[8].lexeme == "0.5");
    assert(floatTokens[8].type == TokenType::Number);
    assert(floatTokens[8].line == 2 && floatTokens[8].column == 14);

    // Verify all supported structural punctuation characters.
    const std::string expectedPunctuation = "(){}[],;";

    const std::vector<Token> punctuationTokens =
        tokenize(expectedPunctuation);

    assert(punctuationTokens.size() == expectedPunctuation.size());

    // Verify every punctuation token and its source location.
    for (std::size_t i = 0; i < expectedPunctuation.size(); ++i)
    {
        assert(punctuationTokens[i].type == TokenType::Punctuation);

        assert(punctuationTokens[i].lexeme ==
               expectedPunctuation.substr(i, 1));

        assert(punctuationTokens[i].line == 1);
        assert(punctuationTokens[i].column == i + 1);
    }

    // Verify all currently supported single-character operators.
    const std::string expectedOperators = "+-*/%&=";

    const std::vector<Token> operatorTokens =
        tokenize(expectedOperators);

    assert(operatorTokens.size() == expectedOperators.size());

    // Verify each operator's category, lexeme, and source location.
    for (std::size_t i = 0; i < expectedOperators.size(); ++i)
    {
        assert(operatorTokens[i].type == TokenType::Operator);

        assert(operatorTokens[i].lexeme ==
               expectedOperators.substr(i, 1));

        assert(operatorTokens[i].line == 1);
        assert(operatorTokens[i].column == i + 1);
    }

    // Verify supported compound-assignment operators.
    const std::vector<Token> compoundTokens =
        tokenize("+= -= *= /=");

    const std::vector<std::string> expectedCompound = {
        "+=", "-=", "*=", "/="};

    assert(compoundTokens.size() == expectedCompound.size());

    // Verify token text, category, and source position.
    for (std::size_t i = 0; i < expectedCompound.size(); ++i)
    {
        assert(compoundTokens[i].lexeme == expectedCompound[i]);
        assert(compoundTokens[i].type == TokenType::Operator);

        assert(compoundTokens[i].line == 1);
        assert(compoundTokens[i].column == 3 * i + 1);
    }

    // Verify equality, increment, and decrement operators.
    const std::vector<Token> twoCharTokens =
        tokenize("== ++ --");

    const std::vector<std::string> expectedTwoChar = {
        "==", "++", "--"};

    assert(twoCharTokens.size() == expectedTwoChar.size());

    // Verify each two-character operator and its position.
    for (std::size_t i = 0; i < expectedTwoChar.size(); ++i)
    {
        assert(twoCharTokens[i].lexeme == expectedTwoChar[i]);
        assert(twoCharTokens[i].type == TokenType::Operator);

        assert(twoCharTokens[i].line == 1);
        assert(twoCharTokens[i].column == 3 * i + 1);
    }

    std::cout << "Tokenizer keyword, identifier, number, punctuation, and operator smoke tests passed.\n";

    return 0;
}