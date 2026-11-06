#pragma once

#include <cstddef>
#include <ostream>
#include <string>
#include <vector>

#include "code_region.hpp"

enum class CloneCandidateKind
{
    Type1,
    Type2Only
};

struct CloneSummaryEntry
{
    CloneCandidateKind kind;
    std::string firstPath;
    std::size_t firstStartLine;
    std::size_t firstEndLine;
    std::string secondPath;
    std::size_t secondStartLine;
    std::size_t secondEndLine;
};

// Extract and retain the original source locations for a valid body match.
bool appendCloneSummaryEntry(
    std::vector<CloneSummaryEntry> &entries,
    CloneCandidateKind kind,
    const std::string &firstRelativePath,
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::string &secondRelativePath,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion);

// Print detailed candidates after the aggregate Type-1/Type-2 totals.
void printCloneSummaryDetails(
    std::ostream &output,
    const std::vector<CloneSummaryEntry> &entries);
