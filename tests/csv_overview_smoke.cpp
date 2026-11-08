#include <iostream>
#include <sstream>
#include <string>

#include "../src/csv_export.hpp"

int main()
{
    AnalysisReport report;

    report.studentFolderCount = 22;
    report.comparedFilePairs = 2145;

    report.aggregate.fileCount = 66;
    report.aggregate.totalLines = 6973;
    report.aggregate.blankLines = 242;
    report.aggregate.totalTokens = 30995;
    report.aggregate.totalRecognizedFunctionBodies = 242;
    report.aggregate.type1CandidateCount = 10;
    report.aggregate.type2OnlyCandidateCount = 10;

    std::ostringstream output;

    writeAnalysisOverviewCsv(output, report);

    const std::string expected =
        "metric,value\n"
        "student_folders,22\n"
        "source_files,66\n"
        "compared_file_pairs,2145\n"
        "total_source_lines,6973\n"
        "blank_source_lines,242\n"
        "total_tokens,30995\n"
        "recognized_function_bodies,242\n"
        "type1_candidate_pairs,10\n"
        "type2_only_candidate_pairs,10\n";

    const bool overviewPassed =
        output.str() == expected;

    AnalysisReport emptyReport;

    std::ostringstream emptyOutput;

    writeAnalysisOverviewCsv(emptyOutput, emptyReport);

    const bool emptyPassed =
        emptyOutput.str().find("student_folders,0\n") !=
            std::string::npos &&
        emptyOutput.str().find("source_files,0\n") !=
            std::string::npos &&
        emptyOutput.str().find("type1_candidate_pairs,0\n") !=
            std::string::npos;

    std::cout << "CSV overview values: "
              << (overviewPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty report handling: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (overviewPassed && emptyPassed) ? 0 : 1;
}