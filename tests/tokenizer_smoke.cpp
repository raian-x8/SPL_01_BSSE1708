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

    assert(numericTokens.size() == 8);

    // Verify the first decimal integer.
    assert(numericTokens[2].lexeme == "123");
    assert(numericTokens[2].type == TokenType::Number);
    assert(numericTokens[2].line == 1 && numericTokens[2].column == 9);

    // Verify the second decimal integer.
    assert(numericTokens[6].lexeme == "45");
    assert(numericTokens[6].type == TokenType::Number);
    assert(numericTokens[6].line == 2 && numericTokens[6].column == 11);

    // Test basic floating-point literal recognition.
    const std::vector<Token> floatTokens =
        tokenize("double pi = 3.14;\nfloat rate = 0.5;");

    assert(floatTokens.size() == 8);

    // Verify the first floating-point literal.
    assert(floatTokens[2].lexeme == "3.14");
    assert(floatTokens[2].type == TokenType::Number);
    assert(floatTokens[2].line == 1 && floatTokens[2].column == 13);

    // Verify the second floating-point literal.
    assert(floatTokens[6].lexeme == "0.5");
    assert(floatTokens[6].type == TokenType::Number);
    assert(floatTokens[6].line == 2 && floatTokens[6].column == 14);

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

    std::cout << "Tokenizer keyword, identifier, number, and punctuation smoke tests passed.\n";

    return 0;
}