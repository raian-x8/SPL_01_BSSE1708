#include "comment_history.hpp"

#include <algorithm>
#include <cmath>

namespace
{
    constexpr std::size_t minimumNonblankLines = 20;
    constexpr double historyTolerance = 0.10;
    constexpr double deviationThreshold = 0.20;

    bool isUsableSample(const CommentHistorySample &sample)
    {
        if (sample.blankLines > sample.totalLines)
        {
            return false;
        }

        const std::size_t nonblankLines =
            sample.totalLines - sample.blankLines;

        return nonblankLines >= minimumNonblankLines &&
               sample.commentLines <= nonblankLines;
    }

    double calculateCommentRate(
        const CommentHistorySample &sample)
    {
        const std::size_t nonblankLines =
            sample.totalLines - sample.blankLines;

        return static_cast<double>(sample.commentLines) /
               static_cast<double>(nonblankLines);
    }
}

CommentHistoryResult analyzeCommentHistory(
    const std::vector<CommentHistorySample> &historicalFiles,
    const CommentHistorySample &currentFile)
{
    CommentHistoryResult result;

    if (historicalFiles.size() < 2 ||
        !isUsableSample(currentFile))
    {
        return result;
    }

    std::size_t totalHistoricalComments = 0;
    std::size_t totalHistoricalNonblankLines = 0;

    double minimumRate = 1.0;
    double maximumRate = 0.0;

    for (const CommentHistorySample &file : historicalFiles)
    {
        if (!isUsableSample(file))
        {
            return result;
        }

        const std::size_t nonblankLines =
            file.totalLines - file.blankLines;

        totalHistoricalComments += file.commentLines;
        totalHistoricalNonblankLines += nonblankLines;

        const double rate = calculateCommentRate(file);

        minimumRate = std::min(minimumRate, rate);
        maximumRate = std::max(maximumRate, rate);
    }

    result.sufficientData = true;

    result.historicalCommentRate =
        static_cast<double>(totalHistoricalComments) /
        static_cast<double>(totalHistoricalNonblankLines);

    result.currentCommentRate =
        calculateCommentRate(currentFile);

    // Historical submissions must show a reasonably consistent rate.
    if (maximumRate - minimumRate > historyTolerance)
    {
        return result;
    }

    result.stableHistoricalRate = true;

    // Detect a substantial change in the current submission.
    const double difference = std::fabs(
        result.currentCommentRate -
        result.historicalCommentRate);

    if (difference >= deviationThreshold)
    {
        result.reviewRecommended = true;
    }

    return result;
}