#include "../src/tokenizer.hpp"

#include <cassert>
#include <iostream>

int main()
{
    // Test keyword classification, identifiers, and source positions.

    const std::vector<Token> tokens =
        tokenize("int total_2;\n_value");

    assert(tokens.size() == 3);

    assert(tokens[0].lexeme == "int");
    assert(tokens[0].type == TokenType::Keyword);
    assert(tokens[0].line == 1 && tokens[0].column == 1);

    assert(tokens[1].lexeme == "total_2");
    assert(tokens[1].type == TokenType::Identifier);
    assert(tokens[1].line == 1 && tokens[1].column == 5);

    assert(tokens[2].lexeme == "_value");
    assert(tokens[2].type == TokenType::Identifier);
    assert(tokens[2].line == 2 && tokens[2].column == 1);

    // Test decimal integer recognition across multiple lines.
    const std::vector<Token> numericTokens =
        tokenize("int x = 123;\nfloat y = 45;");

    assert(numericTokens.size() == 6);

    // Verify the first decimal integer.
    assert(numericTokens[2].lexeme == "123");
    assert(numericTokens[2].type == TokenType::Number);
    assert(numericTokens[2].line == 1 && numericTokens[2].column == 9);

    // Verify the second decimal integer.
    assert(numericTokens[5].lexeme == "45");
    assert(numericTokens[5].type == TokenType::Number);
    assert(numericTokens[5].line == 2 && numericTokens[5].column == 11);

    std::cout << "Tokenizer keyword, identifier, and number smoke tests passed.\n";

    return 0;
}