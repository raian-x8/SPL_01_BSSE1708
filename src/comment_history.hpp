#pragma once

#include <cstddef>
#include <vector>

struct CommentHistorySample
{
    std::size_t totalLines = 0;
    std::size_t blankLines = 0;
    std::size_t commentLines = 0;
};

struct CommentHistoryResult
{
    bool sufficientData = false;
    bool stableHistoricalRate = false;
    bool reviewRecommended = false;

    double historicalCommentRate = 0.0;
    double currentCommentRate = 0.0;
};

CommentHistoryResult analyzeCommentHistory(
    const std::vector<CommentHistorySample> &historicalFiles,
    const CommentHistorySample &currentFile);