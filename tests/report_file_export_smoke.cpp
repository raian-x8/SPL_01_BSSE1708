#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>

#include "../src/report_file_export.hpp"

namespace fs = std::filesystem;

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

    // Check whether a report file exists and contains data.
    auto nonEmptyFile = [](const fs::path &path) -> bool
    {
        std::error_code ec;

        if (!fs::is_regular_file(path, ec) || ec)
        {
            return false;
        }

        return fs::file_size(path, ec) > 0 && !ec;
    };

    // First export.
    fs::path firstDirectory;
    std::string firstError;

    const bool firstPassed =
        exportAnalysisReportFiles(
            report,
            "clonescope_reports",
            firstDirectory,
            firstError);

    if (!firstPassed)
    {
        std::cerr << firstError << '\n';
    }

    const bool filesPassed =
        firstPassed &&
        nonEmptyFile(firstDirectory / "analysis_overview.csv") &&
        nonEmptyFile(firstDirectory / "clone_candidates.csv") &&
        nonEmptyFile(firstDirectory / "student_findings.csv") &&
        nonEmptyFile(firstDirectory / "analysis_report.json");

    // Second export.
    fs::path secondDirectory;
    std::string secondError;

    const bool secondPassed =
        exportAnalysisReportFiles(
            report,
            "clonescope_reports",
            secondDirectory,
            secondError);

    if (!secondPassed)
    {
        std::cerr << secondError << '\n';
    }

    const bool uniquePassed =
        firstPassed &&
        secondPassed &&
        firstDirectory != secondDirectory &&
        nonEmptyFile(firstDirectory / "analysis_report.json") &&
        nonEmptyFile(secondDirectory / "analysis_report.json");

    // An existing source file cannot be used as a directory.
    fs::path invalidDirectory;
    std::string invalidError;

    const bool invalidPassed =
        !exportAnalysisReportFiles(
            report,
            "src/main.cpp",
            invalidDirectory,
            invalidError) &&
        !invalidError.empty();

    std::cout << "First export: "
              << (firstPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Four nonempty report files: "
              << (filesPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Second export: "
              << (secondPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Unique run directories: "
              << (uniquePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Invalid output location: "
              << (invalidPassed ? "PASS" : "FAIL") << '\n';

    if (firstPassed)
    {
        std::cout << "First directory: "
                  << firstDirectory.string() << '\n';
    }

    if (secondPassed)
    {
        std::cout << "Second directory: "
                  << secondDirectory.string() << '\n';
    }

    return (firstPassed &&
            filesPassed &&
            secondPassed &&
            uniquePassed &&
            invalidPassed)
               ? 0
               : 1;
}