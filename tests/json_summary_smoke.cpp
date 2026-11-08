#include <iostream>
#include <sstream>
#include <string>

#include "../src/json_export.hpp"

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

    writeJsonSummary(output, report);

    const std::string expected =
        "{\n"
        "  \"dataset_overview\": {\n"
        "    \"student_folders\": 22,\n"
        "    \"source_files\": 66,\n"
        "    \"compared_file_pairs\": 2145\n"
        "  },\n"
        "  \"source_statistics\": {\n"
        "    \"total_source_lines\": 6973,\n"
        "    \"blank_source_lines\": 242,\n"
        "    \"total_tokens\": 30995,\n"
        "    \"recognized_function_bodies\": 242\n"
        "  },\n"
        "  \"clone_detection\": {\n"
        "    \"type1_candidate_pairs\": 10,\n"
        "    \"type2_only_candidate_pairs\": 10,\n"
        "    \"total_candidate_pairs\": 20\n"
        "  }\n"
        "}";

    const bool summaryPassed =
        output.str() == expected;

    AnalysisReport emptyReport;

    std::ostringstream emptyOutput;

    writeJsonSummary(emptyOutput, emptyReport);

    const bool emptyPassed =
        emptyOutput.str().find(
            "\"student_folders\": 0") != std::string::npos &&
        emptyOutput.str().find(
            "\"source_files\": 0") != std::string::npos &&
        emptyOutput.str().find(
            "\"total_candidate_pairs\": 0") != std::string::npos;

    std::cout << "JSON summary values: "
              << (summaryPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty JSON summary: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (summaryPassed && emptyPassed) ? 0 : 1;
}