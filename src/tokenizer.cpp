#include "tokenizer.hpp"

#include <cctype>

#include <unordered_set>

// Converts C/C++ source text into tokens.
// Currently recognizes identifiers, selected keywords,
// basic decimal numeric literals, structural punctuation,
// and selected single-character operators.

std::vector<Token> tokenize(const std::string &source)
{
    std::vector<Token> tokens;

    // Common C/C++ keywords; the list will be expanded later.
    static const std::unordered_set<std::string> keywords = {
        "int", "float", "double", "char", "void",
        "if", "else", "for", "while", "return",
        "bool", "const", "class", "struct"};

    // Single-character structural punctuation supported by the tokenizer.
    static const std::string punctuation = "(){}[],;";

    // Basic single-character operators.
    // Multi-character operators will be handled in a later step.
    static const std::string singleCharOperators = "+-*/%&=";

    // Supported two-character operators, including compound assignments.
    // Checked before single-character operators to preserve longest matches.
    static const std::unordered_set<std::string> twoCharOperators = {
        "==", "++", "--",
        "+=", "-=", "*=", "/="};

    // Track the current character and source location.
    std::size_t index = 0;
    std::size_t line = 1;
    std::size_t column = 1;

    while (index < source.size())
    {
        char current = source[index];

        // Recognize an identifier beginning with a letter or underscore.
        unsigned char ch = static_cast<unsigned char>(current);

        if (std::isalpha(ch) || current == '_')
        {
            std::size_t start = index;
            std::size_t startColumn = column;

            // Consume all characters belonging to the identifier.
            while (index < source.size())
            {
                unsigned char next =
                    static_cast<unsigned char>(source[index]);

                if (!std::isalnum(next) && source[index] != '_')
                {
                    break;
                }

                ++index;
                ++column;
            }

            // Extract the complete identifier-shaped word.
            std::string lexeme = source.substr(start, index - start);

            // Distinguish reserved keywords from ordinary identifiers.
            TokenType type = TokenType::Identifier;

            if (keywords.find(lexeme) != keywords.end())
            {
                type = TokenType::Keyword;
            }

            // Preserve the token text and its starting location.
            tokens.push_back(Token{
                type,
                lexeme,
                line,
                startColumn});

            continue;
        }

        // Recognize a decimal integer literal or a floating point literal
        if (std::isdigit(ch))
        {
            std::size_t start = index;
            std::size_t startColumn = column;

            // Consume consecutive decimal digits.
            while (index < source.size())
            {
                unsigned char next =
                    static_cast<unsigned char>(source[index]);

                if (!std::isdigit(next))
                {
                    break;
                }

                ++index;
                ++column;
            }

            // Recognize an optional fractional part when a digit
            // immediately follows the decimal point.
            if (index + 1 < source.size() &&
                source[index] == '.' &&
                std::isdigit(static_cast<unsigned char>(source[index + 1])))
            {
                // Consume the decimal point.
                ++index;
                ++column;

                // Consume the digits after the decimal point.
                while (index < source.size())
                {
                    unsigned char next =
                        static_cast<unsigned char>(source[index]);

                    if (!std::isdigit(next))
                    {
                        break;
                    }

                    ++index;
                    ++column;
                }
            }

            // Store the number and its starting location.
            tokens.push_back(Token{
                TokenType::Number,
                source.substr(start, index - start),
                line,
                startColumn});

            continue;
        }

        // Recognize single-character structural punctuation.
        if (punctuation.find(current) != std::string::npos)
        {
            // Store the punctuation and its source location.
            tokens.push_back(Token{
                TokenType::Punctuation,
                source.substr(index, 1),
                line,
                column});

            ++index;
            ++column;

            continue;
        }

        // Recognize supported two-character operators first.
        if (index + 1 < source.size())
        {
            std::string pair = source.substr(index, 2);

            if (twoCharOperators.find(pair) != twoCharOperators.end())
            {
                // Preserve the complete operator and its starting location.
                tokens.push_back(Token{
                    TokenType::Operator,
                    pair,
                    line,
                    column});

                index += 2;
                column += 2;

                continue;
            }
        }

        // Recognize a basic single-character operator.
        if (singleCharOperators.find(current) != std::string::npos)
        {
            // Preserve the operator and its source location.
            tokens.push_back(Token{
                TokenType::Operator,
                source.substr(index, 1),
                line,
                column});

            ++index;
            ++column;

            continue;
        }

        if (current == '\n')
        {
            ++line;
            column = 1;
        }
        else
        {
            ++column;
        }

        ++index;
    }

    return tokens;
}