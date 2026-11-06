#pragma once

#include <cstddef>
#include <string>

struct CommentStyleStatistics
{
    std::size_t commentLines = 0;
    std::size_t commentOnlyLines = 0;
    std::size_t inlineCommentLines = 0;
};

CommentStyleStatistics calculateCommentStyleStatistics(
    const std::string &sourceCode,
    const std::string &cleanedCode);