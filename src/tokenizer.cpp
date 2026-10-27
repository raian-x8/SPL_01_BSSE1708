#include "tokenizer.hpp"

#include <cctype>

// Scans source code one character at a time.
// Token recognition will be added incrementally.
std::vector<Token> tokenize(const std::string &source)
{
    std::vector<Token> tokens;

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

            // Save the recognized text and its starting location.
            tokens.push_back(Token{
                TokenType::Identifier,
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