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

    // Separate operators to avoid forming compound assignments.
    const std::vector<Token> operatorTokens =
        tokenize("+ - * / % & =");

    assert(operatorTokens.size() == expectedOperators.size());

    // Verify each operator's category, lexeme, and source location.
    for (std::size_t i = 0; i < expectedOperators.size(); ++i)
    {
        assert(operatorTokens[i].type == TokenType::Operator);

        assert(operatorTokens[i].lexeme ==
               expectedOperators.substr(i, 1));

        assert(operatorTokens[i].line == 1);
        assert(operatorTokens[i].column == 2 * i + 1);
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

    // Verify comparison and logical operators.
    const std::vector<Token> logicalTokens =
        tokenize("!= <= >= && ||");

    const std::vector<std::string> expectedLogical = {
        "!=", "<=", ">=", "&&", "||"};

    assert(logicalTokens.size() == expectedLogical.size());

    // Verify each operator's text, category, and position.
    for (std::size_t i = 0; i < expectedLogical.size(); ++i)
    {
        assert(logicalTokens[i].lexeme == expectedLogical[i]);
        assert(logicalTokens[i].type == TokenType::Operator);

        assert(logicalTokens[i].line == 1);
        assert(logicalTokens[i].column == 3 * i + 1);
    }

    // Verify newly supported single-character operators.
    const std::string additionalOperators = "!<>|^~";

    const std::vector<Token> additionalTokens =
        tokenize(additionalOperators);

    assert(additionalTokens.size() == additionalOperators.size());

    // Verify each operator's type, text, and source position.
    for (std::size_t i = 0; i < additionalOperators.size(); ++i)
    {
        assert(additionalTokens[i].type == TokenType::Operator);

        assert(additionalTokens[i].lexeme ==
               additionalOperators.substr(i, 1));

        assert(additionalTokens[i].line == 1);
        assert(additionalTokens[i].column == i + 1);
    }

    // Verify the remaining supported compound-assignment operators.
    const std::vector<Token> extraCompoundTokens =
        tokenize("%= &= |= ^=");

    const std::vector<std::string> expectedExtraCompound = {
        "%=", "&=", "|=", "^="};

    assert(extraCompoundTokens.size() == expectedExtraCompound.size());

    // Verify each operator's lexeme, category, and source position.
    for (std::size_t i = 0; i < expectedExtraCompound.size(); ++i)
    {
        assert(extraCompoundTokens[i].lexeme == expectedExtraCompound[i]);
        assert(extraCompoundTokens[i].type == TokenType::Operator);

        assert(extraCompoundTokens[i].line == 1);
        assert(extraCompoundTokens[i].column == 3 * i + 1);
    }

    // Verify that an entire quoted string becomes one token.
    const std::vector<Token> stringTokens =
        tokenize("\"a+b\"");

    assert(stringTokens.size() == 1);

    assert(stringTokens[0].type == TokenType::StringLiteral);
    assert(stringTokens[0].lexeme == "\"a+b\"");

    assert(stringTokens[0].line == 1);
    assert(stringTokens[0].column == 1);

    // Verify that an escaped quote does not terminate a string.
    const std::string escapedQuoteSource = "\"a\\\"+b\"";

    const std::vector<Token> escapedQuoteTokens =
        tokenize(escapedQuoteSource);

    assert(escapedQuoteTokens.size() == 1);

    assert(escapedQuoteTokens[0].type == TokenType::StringLiteral);
    assert(escapedQuoteTokens[0].lexeme == escapedQuoteSource);

    assert(escapedQuoteTokens[0].line == 1);
    assert(escapedQuoteTokens[0].column == 1);

    // Verify escaped backslashes before a closing quotation mark.
    const std::string escapedBackslashSource = "\"path\\\\\"";

    const std::vector<Token> escapedBackslashTokens =
        tokenize(escapedBackslashSource);

    assert(escapedBackslashTokens.size() == 1);

    assert(escapedBackslashTokens[0].type == TokenType::StringLiteral);
    assert(escapedBackslashTokens[0].lexeme == escapedBackslashSource);

    assert(escapedBackslashTokens[0].line == 1);
    assert(escapedBackslashTokens[0].column == 1);

    // Verify that a single-quoted character becomes one token.
    const std::vector<Token> charTokens =
        tokenize("'A'");

    assert(charTokens.size() == 1);

    assert(charTokens[0].type == TokenType::CharLiteral);
    assert(charTokens[0].lexeme == "'A'");

    assert(charTokens[0].line == 1);
    assert(charTokens[0].column == 1);

    // Verify a character literal containing an escaped newline.
    const std::string escapedNewlineCharSource = "'\\n'";

    const std::vector<Token> escapedNewlineCharTokens =
        tokenize(escapedNewlineCharSource);

    assert(escapedNewlineCharTokens.size() == 1);

    assert(escapedNewlineCharTokens[0].type == TokenType::CharLiteral);
    assert(escapedNewlineCharTokens[0].lexeme == escapedNewlineCharSource);

    assert(escapedNewlineCharTokens[0].line == 1);
    assert(escapedNewlineCharTokens[0].column == 1);

    // Verify a character literal containing an escaped single quote.
    const std::string escapedSingleQuoteSource = "'\\''";

    const std::vector<Token> escapedSingleQuoteTokens =
        tokenize(escapedSingleQuoteSource);

    assert(escapedSingleQuoteTokens.size() == 1);

    assert(escapedSingleQuoteTokens[0].type == TokenType::CharLiteral);
    assert(escapedSingleQuoteTokens[0].lexeme == escapedSingleQuoteSource);

    assert(escapedSingleQuoteTokens[0].line == 1);
    assert(escapedSingleQuoteTokens[0].column == 1);

    // Verify that an unterminated string is not treated as valid.
    const std::string unterminatedStringSource = "\"unfinished";

    const std::vector<Token> unterminatedStringTokens =
        tokenize(unterminatedStringSource);

    assert(unterminatedStringTokens.size() == 1);

    assert(unterminatedStringTokens[0].type == TokenType::Unknown);
    assert(unterminatedStringTokens[0].lexeme == unterminatedStringSource);

    assert(unterminatedStringTokens[0].line == 1);
    assert(unterminatedStringTokens[0].column == 1);

    // Verify that an unterminated character is not treated as valid.
    const std::string unterminatedCharSource = "'A";

    const std::vector<Token> unterminatedCharTokens =
        tokenize(unterminatedCharSource);

    assert(unterminatedCharTokens.size() == 1);

    assert(unterminatedCharTokens[0].type == TokenType::Unknown);
    assert(unterminatedCharTokens[0].lexeme == unterminatedCharSource);

    assert(unterminatedCharTokens[0].line == 1);
    assert(unterminatedCharTokens[0].column == 1);

    // Verify that an unterminated string stops at a newline.
    const std::string multilineSource = "\"unfinished\nint x";

    const std::vector<Token> multilineTokens =
        tokenize(multilineSource);

    assert(multilineTokens.size() == 3);

    // The incomplete string belongs to the first line.
    assert(multilineTokens[0].type == TokenType::Unknown);
    assert(multilineTokens[0].lexeme == "\"unfinished");
    assert(multilineTokens[0].line == 1);
    assert(multilineTokens[0].column == 1);

    // The keyword on the next line must still be recognized.
    assert(multilineTokens[1].type == TokenType::Keyword);
    assert(multilineTokens[1].lexeme == "int");
    assert(multilineTokens[1].line == 2);
    assert(multilineTokens[1].column == 1);

    // Verify the following identifier and its position.
    assert(multilineTokens[2].type == TokenType::Identifier);
    assert(multilineTokens[2].lexeme == "x");
    assert(multilineTokens[2].line == 2);
    assert(multilineTokens[2].column == 5);

    // Verify that an unterminated character stops at a newline.
    const std::string multilineCharSource = "'A\nint x";

    const std::vector<Token> multilineCharTokens =
        tokenize(multilineCharSource);

    assert(multilineCharTokens.size() == 3);

    // Verify the malformed character on the first line.
    assert(multilineCharTokens[0].type == TokenType::Unknown);
    assert(multilineCharTokens[0].lexeme == "'A");
    assert(multilineCharTokens[0].line == 1);
    assert(multilineCharTokens[0].column == 1);

    // Verify the keyword on the second line.
    assert(multilineCharTokens[1].type == TokenType::Keyword);
    assert(multilineCharTokens[1].lexeme == "int");
    assert(multilineCharTokens[1].line == 2);
    assert(multilineCharTokens[1].column == 1);

    // Verify the following identifier.
    assert(multilineCharTokens[2].type == TokenType::Identifier);
    assert(multilineCharTokens[2].lexeme == "x");
    assert(multilineCharTokens[2].line == 2);
    assert(multilineCharTokens[2].column == 5);

    // Verify that an unsupported character is preserved.
    const std::vector<Token> unknownTokens =
        tokenize("int x @ 5;");

    assert(unknownTokens.size() == 5);

    // Verify the unsupported character.
    assert(unknownTokens[2].type == TokenType::Unknown);
    assert(unknownTokens[2].lexeme == "@");
    assert(unknownTokens[2].line == 1);
    assert(unknownTokens[2].column == 7);

    // Verify that tokenization continues afterward.
    assert(unknownTokens[3].type == TokenType::Number);
    assert(unknownTokens[3].lexeme == "5");
    assert(unknownTokens[3].column == 9);

    assert(unknownTokens[4].type == TokenType::Punctuation);
    assert(unknownTokens[4].lexeme == ";");
    assert(unknownTokens[4].column == 10);

    std::cout << "All tokenizer smoke tests passed.\n";

    return 0;
}