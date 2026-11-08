#include <iostream>

#include "../src/json_export.hpp"

int main()
{
    AnalysisReport report;

    report.studentFolderCount = 2;
    report.comparedFilePairs = 1;

    report.aggregate.fileCount = 2;
    report.aggregate.type1CandidateCount = 1;

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type1,
        "student01/assignment3.cpp", 4, 29,
        "student02/assignment3.cpp", 4, 29});

    report.studentFindings.push_back(
        StudentStyleFinding{"student01", true, true, true, false});

    writeAnalysisReportJson(std::cout, report);

    return std::cout ? 0 : 1;
}