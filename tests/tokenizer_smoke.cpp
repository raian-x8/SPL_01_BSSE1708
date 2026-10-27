#include "../src/tokenizer.hpp"

#include <cassert>
#include <iostream>

int main()
{
    // Test identifier recognition and source positions.
    const std::vector<Token> tokens =
        tokenize("int total_2;\n_value");

    assert(tokens.size() == 3);

    assert(tokens[0].lexeme == "int");
    assert(tokens[0].type == TokenType::Identifier);
    assert(tokens[0].line == 1 && tokens[0].column == 1);

    assert(tokens[1].lexeme == "total_2");
    assert(tokens[1].line == 1 && tokens[1].column == 5);

    assert(tokens[2].lexeme == "_value");
    assert(tokens[2].line == 2 && tokens[2].column == 1);

    std::cout << "Identifier smoke test passed.\n";

    return 0;
}