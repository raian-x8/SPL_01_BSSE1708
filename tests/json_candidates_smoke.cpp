#include <iostream>
#include <sstream>
#include <string>

#include "../src/json_export.hpp"

int main()
{
    AnalysisReport report;

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type1,
        "student01/assignment3.cpp", 4, 29,
        "student17/assignment3.cpp", 4, 29});

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type2Only,
        "student05/assignment3.cpp", 34, 64,
        "student12/assignment3.cpp", 32, 62});

    std::ostringstream output;

    writeJsonCloneCandidates(output, report);

    const std::string text = output.str();

    const bool typesPassed =
        text.find("\"type\": \"Type-1\"") != std::string::npos &&
        text.find("\"type\": \"Type-2-only\"") != std::string::npos;

    const bool pathsPassed =
        text.find("\"path\": \"student01/assignment3.cpp\"") !=
            std::string::npos &&
        text.find("\"path\": \"student12/assignment3.cpp\"") !=
            std::string::npos;

    const bool locationsPassed =
        text.find("\"start_line\": 34") != std::string::npos &&
        text.find("\"end_line\": 62") != std::string::npos;

    const bool separatorPassed =
        text.find("  },\n  {") != std::string::npos;

    AnalysisReport emptyReport;
    std::ostringstream emptyOutput;

    writeJsonCloneCandidates(emptyOutput, emptyReport);

    const bool emptyPassed =
        emptyOutput.str() == "[]";

    AnalysisReport specialReport;

    specialReport.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type1,
        "student01/assignment\"3.cpp", 4, 29,
        "student17/assignment3.cpp", 4, 29});

    std::ostringstream specialOutput;

    writeJsonCloneCandidates(specialOutput, specialReport);

    const bool escapingPassed =
        specialOutput.str().find("assignment\\\"3.cpp") !=
        std::string::npos;

    std::cout << "Clone classifications: "
              << (typesPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Source paths: "
              << (pathsPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Source line ranges: "
              << (locationsPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Array separators: "
              << (separatorPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty candidate array: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "JSON path escaping: "
              << (escapingPassed ? "PASS" : "FAIL") << '\n';

    return (typesPassed &&
            pathsPassed &&
            locationsPassed &&
            separatorPassed &&
            emptyPassed &&
            escapingPassed)
               ? 0
               : 1;
}