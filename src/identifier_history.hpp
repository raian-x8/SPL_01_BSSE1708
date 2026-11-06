#pragma once

#include <vector>

#include "identifier_style.hpp"

struct IdentifierHistoryResult
{
    bool sufficientData = false;
    bool stableHistoricalStyle = false;
    bool reviewRecommended = false;

    IdentifierStyle historicalDominantStyle =
        IdentifierStyle::Other;

    IdentifierStyle currentDominantStyle =
        IdentifierStyle::Other;
};

IdentifierHistoryResult analyzeIdentifierHistory(
    const std::vector<IdentifierStyleStatistics> &historicalFiles,
    const IdentifierStyleStatistics &currentFile);