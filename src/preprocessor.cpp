
#include "preprocessor.hpp"
#include <cstddef>

enum class ScanState
{
    Normal,
    LineComment,
    BlockComment,
    StringLiteral,
    CharLiteral
};

// Basic comment removal using a lexical state machine.
// Preserves source positions for supported comment cases.

std::string removeComments(const std::string &source)
{
    ScanState state = ScanState::Normal;
    std::string result;

    // Visit every character in the original source

    for (std::size_t i = 0; i < source.size(); ++i)
    {
        char current = source[i];

        if (state == ScanState::Normal)
        {
            if (current == '/' && i + 1 < source.size() &&
                source[i + 1] == '/')
            {
                state = ScanState::LineComment;
                result += "  ";
                ++i;
            }

            else if (current == '/' && i + 1 < source.size() &&
                     source[i + 1] == '*')
            {
                state = ScanState::BlockComment;
                result += "  ";
                ++i;
            }

            else if (current == '"')
            {
                state = ScanState::StringLiteral;
                result += current;
            }
            else if (current == '\'')
            {
                state = ScanState::CharLiteral;
                result += current;
            }
            else
            {
                result += current;
            }
        }
        else if (state == ScanState::LineComment)
        {
            if (current == '\n')
            {
                result += '\n';
                state = ScanState::Normal;
            }
            else
            {
                result += ' ';
            }
        }

        else if (state == ScanState::BlockComment)
        {
            if (current == '*' && i + 1 < source.size() &&
                source[i + 1] == '/')
            {
                result += "  ";
                state = ScanState::Normal;
                ++i;
            }
            else if (current == '\n')
            {
                result += '\n';
            }
            else
            {
                result += ' ';
            }
        }

        else if (state == ScanState::StringLiteral)
        {
            // Recover when an ordinary string reaches a physical newline.
            if (current == '\n')
            {
                result += '\n';
                state = ScanState::Normal;
            }
            else if (current == '\\' &&
                     i + 1 < source.size() &&
                     source[i + 1] != '\n')
            {
                // Preserve an escape sequence without crossing a newline.
                result += current;
                result += source[i + 1];
                ++i;
            }
            else if (current == '"')
            {
                // A closing quotation mark ends the string.
                result += current;
                state = ScanState::Normal;
            }
            else
            {
                result += current;
            }
        }

        else if (state == ScanState::CharLiteral)
        {
            // Recover when an ordinary character literal reaches a newline.
            if (current == '\n')
            {
                result += '\n';
                state = ScanState::Normal;
            }
            else if (current == '\\' &&
                     i + 1 < source.size() &&
                     source[i + 1] != '\n')
            {
                // Preserve an escape sequence without crossing a newline.
                result += current;
                result += source[i + 1];
                ++i;
            }
            else if (current == '\'')
            {
                // A closing single quotation mark ends the character literal.
                result += current;
                state = ScanState::Normal;
            }
            else
            {
                result += current;
            }
        }
    }

    return result;
}