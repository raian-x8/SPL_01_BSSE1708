#pragma once

#include <cstddef>

#include <string>

struct SourceStatistics
{
    std::size_t totalLines = 0;
    std::size_t blankLines = 0;
    std::size_t tokenCount = 0;
    std::size_t recognizedFunctionBodies = 0;
};

SourceStatistics calculateSourceStatistics(
    const std::string &sourceCode,
    std::size_t tokenCount,
    std::size_t recognizedFunctionBodies);