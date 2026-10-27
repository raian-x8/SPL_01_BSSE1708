#include "../src/preprocessor.hpp"
#include "../src/tokenizer.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    // Open an actual C source file.
    std::ifstream file("samples/hello.c");

    assert(file.is_open());

    // Read its complete contents.
    std::ostringstream buffer;
    buffer << file.rdbuf();

    // Preprocess and tokenize the source.
    const std::string cleanedCode =
        removeComments(buffer.str());

    const std::vector<Token> tokens =
        tokenize(cleanedCode);

    // Verify the previously observed token count.
    assert(tokens.size() == 28);

    // Verify the main function's return-type keyword.
    assert(tokens[7].type == TokenType::Keyword);
    assert(tokens[7].lexeme == "int");

    // Verify a complete string literal from the actual file.
    assert(tokens[19].type == TokenType::StringLiteral);
    assert(tokens[19].lexeme == "\"Number: %d\\n\"");

    // The current tokenizer does not recognize
    // preprocessor directives as complete constructs.
    assert(tokens[0].type == TokenType::Unknown);
    assert(tokens[0].lexeme == "#");

    // Verify that preprocessing preserves token source positions.
    const std::string positionSource =
        "int a; /* note */ int b;\n"
        "// comment\n"
        "int c;";

    const std::vector<Token> positionTokens =
        tokenize(removeComments(positionSource));

    // Comments must not contribute tokens.
    assert(positionTokens.size() == 9);

    // Verify the keyword after a block comment.
    assert(positionTokens[3].type == TokenType::Keyword);
    assert(positionTokens[3].lexeme == "int");
    assert(positionTokens[3].line == 1);
    assert(positionTokens[3].column == 19);

    // Verify the keyword after a line comment.
    assert(positionTokens[6].type == TokenType::Keyword);
    assert(positionTokens[6].lexeme == "int");
    assert(positionTokens[6].line == 3);
    assert(positionTokens[6].column == 1);

    // Verify recovery after an unterminated string.
    const std::string recoverySource =
        "\"unfinished\n"
        "// comment\n"
        "int x;";

    const std::vector<Token> recoveryTokens =
        tokenize(removeComments(recoverySource));

    // The comment should not produce tokens.
    assert(recoveryTokens.size() == 4);

    // The malformed string stays on line 1.
    assert(recoveryTokens[0].type == TokenType::Unknown);
    assert(recoveryTokens[0].lexeme == "\"unfinished");

    // Tokenization resumes correctly on line 3.
    assert(recoveryTokens[1].type == TokenType::Keyword);
    assert(recoveryTokens[1].lexeme == "int");
    assert(recoveryTokens[1].line == 3);
    assert(recoveryTokens[1].column == 1);

    // Verify recovery after an unterminated character literal.
    const std::string charRecoverySource =
        "'A\n"
        "// comment\n"
        "int x;";

    const std::vector<Token> charRecoveryTokens =
        tokenize(removeComments(charRecoverySource));

    // The comment must not produce tokens.
    assert(charRecoveryTokens.size() == 4);

    // The malformed character remains on line 1.
    assert(charRecoveryTokens[0].type == TokenType::Unknown);
    assert(charRecoveryTokens[0].lexeme == "'A");

    // Verify that code on line 3 is recognized.
    assert(charRecoveryTokens[1].type == TokenType::Keyword);
    assert(charRecoveryTokens[1].lexeme == "int");
    assert(charRecoveryTokens[1].line == 3);
    assert(charRecoveryTokens[1].column == 1);

    std::cout << "File pipeline smoke test passed.\n";

    return 0;
}