#include "tokenizer.hpp"

#include <cctype>

#include <unordered_set>

// Converts C/C++ source text into tokens.
// Currently recognizes identifiers, selected keywords, and decimal integers.

std::vector<Token> tokenize(const std::string &source)
{
    std::vector<Token> tokens;

    // Common C/C++ keywords; the list will be expanded later.
    static const std::unordered_set<std::string> keywords = {
        "int", "float", "double", "char", "void",
        "if", "else", "for", "while", "return",
        "bool", "const", "class", "struct"};

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

        // Recognize a decimal integer literal.
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

            // Store the number and its starting location.
            tokens.push_back(Token{
                TokenType::Number,
                source.substr(start, index - start),
                line,
                startColumn});

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