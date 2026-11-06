#include <iostream>
#include <string>
#include <vector>

#include "../src/comment_history.hpp"

bool reportTest(const std::string &name, bool passed)
{
    std::cout << name << ": "
              << (passed ? "PASS" : "FAIL") << '\n';

    return passed;
}

int main()
{
    bool allPassed = true;

    const std::vector<CommentHistorySample> stableHistory = {
        {30, 5, 8},
        {30, 5, 9}};

    // Test 1: A substantial drop in commenting.
    const CommentHistoryResult changed =
        analyzeCommentHistory(stableHistory, {30, 5, 0});

    allPassed = reportTest(
                    "Historical commenting deviation",
                    changed.sufficientData &&
                        changed.stableHistoricalRate &&
                        changed.reviewRecommended) &&
                allPassed;

    // Test 2: The current file follows the historical pattern.
    const CommentHistoryResult consistent =
        analyzeCommentHistory(stableHistory, {30, 5, 8});

    allPassed = reportTest(
                    "Consistent commenting history",
                    consistent.sufficientData &&
                        consistent.stableHistoricalRate &&
                        !consistent.reviewRecommended) &&
                allPassed;

    // Test 3: One historical submission is insufficient.
    const CommentHistoryResult singleHistory =
        analyzeCommentHistory({{30, 5, 8}}, {30, 5, 0});

    allPassed = reportTest(
                    "Single historical submission",
                    !singleHistory.sufficientData) &&
                allPassed;

    // Test 4: Short submissions should not trigger review.
    const CommentHistoryResult shortFiles =
        analyzeCommentHistory(
            {{12, 2, 3}, {30, 5, 8}},
            {30, 5, 0});

    allPassed = reportTest(
                    "Insufficient source lines",
                    !shortFiles.sufficientData) &&
                allPassed;

    // Test 5: Inconsistent history provides no stable baseline.
    const CommentHistoryResult mixedHistory =
        analyzeCommentHistory(
            {{30, 5, 0}, {30, 5, 10}},
            {30, 5, 0});

    allPassed = reportTest(
                    "Mixed historical commenting rates",
                    mixedHistory.sufficientData &&
                        !mixedHistory.stableHistoricalRate &&
                        !mixedHistory.reviewRecommended) &&
                allPassed;

    // Test 6: Small differences should be ignored.
    const CommentHistoryResult smallDifference =
        analyzeCommentHistory(stableHistory, {30, 5, 7});

    allPassed = reportTest(
                    "Small commenting difference",
                    smallDifference.sufficientData &&
                        smallDifference.stableHistoricalRate &&
                        !smallDifference.reviewRecommended) &&
                allPassed;

    // Test 7: Reject impossible comment counts.
    const CommentHistoryResult invalidSample =
        analyzeCommentHistory(
            stableHistory,
            {30, 10, 21});

    allPassed = reportTest(
                    "Invalid comment statistics",
                    !invalidSample.sufficientData) &&
                allPassed;

    // Test 8: Detect an unusually large increase too.
    const CommentHistoryResult increasedComments =
        analyzeCommentHistory(
            {{30, 5, 0}, {30, 5, 0}},
            {30, 5, 8});

    allPassed = reportTest(
                    "Sudden commenting increase",
                    increasedComments.sufficientData &&
                        increasedComments.stableHistoricalRate &&
                        increasedComments.reviewRecommended) &&
                allPassed;

    return allPassed ? 0 : 1;
}