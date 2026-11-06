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

struct AggregateStatistics
{
    std::size_t fileCount = 0;
    std::size_t totalLines = 0;
    std::size_t blankLines = 0;
    std::size_t totalTokens = 0;
    std::size_t totalRecognizedFunctionBodies = 0;

    std::size_t type1CandidateCount = 0;
    std::size_t type2OnlyCandidateCount = 0;
};

void accumulateSourceStatistics(
    AggregateStatistics &aggregate,
    const SourceStatistics &sourceStatistics);