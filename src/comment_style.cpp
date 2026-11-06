#include "comment_style.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

CommentStyleStatistics calculateCommentStyleStatistics(
    const std::string &sourceCode,
    const std::string &cleanedCode)
{
    CommentStyleStatistics statistics;

    std::istringstream originalInput(sourceCode);
    std::istringstream cleanedInput(cleanedCode);

    std::string originalLine;
    std::string cleanedLine;

    // Compare the original and comment-removed source line by line.
    while (std::getline(originalInput, originalLine) &&
           std::getline(cleanedInput, cleanedLine))
    {
        // An unchanged line contains no recognized comments.
        if (originalLine == cleanedLine)
        {
            continue;
        }

        ++statistics.commentLines;

        // Check whether executable code remains after comment removal.
        const bool containsCode = std::any_of(
            cleanedLine.begin(),
            cleanedLine.end(),
            [](unsigned char character)
            {
                return !std::isspace(character);
            });

        if (containsCode)
        {
            ++statistics.inlineCommentLines;
        }
        else
        {
            ++statistics.commentOnlyLines;
        }
    }

    return statistics;
}