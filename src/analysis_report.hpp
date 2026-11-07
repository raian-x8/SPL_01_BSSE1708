#pragma once

#include <cstddef>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "clone_summary.hpp"
#include "source_statistics.hpp"

// Each student receives at most one historical analysis for each style metric.
// A false evaluation flag means insufficient, ambiguous, or unstable history;
// it must not be interpreted as a clean result.
struct StudentStyleFinding
{
    std::string studentId;
    bool namingEvaluated = false;
    bool namingDeviation = false;
    bool commentingEvaluated = false;
    bool commentingDeviation = false;
};

// Gather the results that the analyzer has already computed; reports should
// never run their own clone or stylometry detection a second time.
struct AnalysisReport
{
    std::size_t studentFolderCount = 0;
    std::size_t comparedFilePairs = 0;
    AggregateStatistics aggregate;
    std::vector<CloneSummaryEntry> cloneCandidates;
    std::vector<StudentStyleFinding> studentFindings;
};

// Shared collection of student-wise human-review reasons.
using HumanReviewIndicators =
    std::map<std::string, std::set<std::string>>;

HumanReviewIndicators collectHumanReviewIndicators(
    const AnalysisReport &report);

void printCombinedAnalysisReport(
    std::ostream &output,
    const AnalysisReport &report);
