#include "identifier_history.hpp"

#include <cstddef>

namespace
{
    constexpr std::size_t minimumIdentifiers = 3;
    constexpr double dominanceThreshold = 0.80;

    // Count identifiers that indicate a multiword naming convention.
    std::size_t countConventionIdentifiers(
        const IdentifierStyleStatistics &statistics)
    {
        return statistics.camelCase +
               statistics.pascalCase +
               statistics.snakeCase;
    }

    // Identify a sufficiently dominant naming convention.
    IdentifierStyle findDominantConvention(
        const IdentifierStyleStatistics &statistics)
    {
        const std::size_t total =
            countConventionIdentifiers(statistics);

        if (total < minimumIdentifiers)
        {
            return IdentifierStyle::Other;
        }

        IdentifierStyle dominant = IdentifierStyle::CamelCase;
        std::size_t dominantCount = statistics.camelCase;

        if (statistics.pascalCase > dominantCount)
        {
            dominant = IdentifierStyle::PascalCase;
            dominantCount = statistics.pascalCase;
        }

        if (statistics.snakeCase > dominantCount)
        {
            dominant = IdentifierStyle::SnakeCase;
            dominantCount = statistics.snakeCase;
        }

        const double proportion =
            static_cast<double>(dominantCount) /
            static_cast<double>(total);

        if (proportion < dominanceThreshold)
        {
            return IdentifierStyle::Other;
        }

        return dominant;
    }
}

IdentifierHistoryResult analyzeIdentifierHistory(
    const std::vector<IdentifierStyleStatistics> &historicalFiles,
    const IdentifierStyleStatistics &currentFile)
{
    IdentifierHistoryResult result;

    // Require at least two previous submissions.
    if (historicalFiles.size() < 2)
    {
        return result;
    }

    // Ensure every historical file has enough relevant identifiers.
    for (const IdentifierStyleStatistics &statistics : historicalFiles)
    {
        if (countConventionIdentifiers(statistics) < minimumIdentifiers)
        {
            return result;
        }
    }

    // Ensure the current submission also has enough identifiers.
    if (countConventionIdentifiers(currentFile) < minimumIdentifiers)
    {
        return result;
    }

    result.sufficientData = true;

    IdentifierStyle historicalStyle = IdentifierStyle::Other;

    // Examine the naming convention of each historical submission.
    for (const IdentifierStyleStatistics &statistics : historicalFiles)
    {
        const IdentifierStyle currentHistoricalStyle =
            findDominantConvention(statistics);

        if (currentHistoricalStyle == IdentifierStyle::Other)
        {
            return result;
        }

        if (historicalStyle == IdentifierStyle::Other)
        {
            historicalStyle = currentHistoricalStyle;
        }
        else if (historicalStyle != currentHistoricalStyle)
        {
            return result;
        }
    }

    result.stableHistoricalStyle = true;
    result.historicalDominantStyle = historicalStyle;

    // Determine the current submission's dominant convention.
    result.currentDominantStyle =
        findDominantConvention(currentFile);

    // Recommend review only when a clear convention change exists.
    if (result.currentDominantStyle != IdentifierStyle::Other &&
        result.currentDominantStyle != historicalStyle)
    {
        result.reviewRecommended = true;
    }

    return result;
}