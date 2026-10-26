
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

// Temporary implementation.
// The actual comment-removal algorithm will be added next.

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
            result += current;
        }
    }

    return result;
}
