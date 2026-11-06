#include <iostream>
#include <sstream>
#include <string>

#include "../src/analysis_report.hpp"

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
    report.aggregate.type1CandidateCount = 1;
    report.aggregate.type2OnlyCandidateCount = 1;

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type1,
        "student01/assignment3.cpp", 4, 29,
        "student17/assignment3.cpp", 4, 29});

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type2Only,
        "student05/assignment3.cpp", 34, 64,
        "student11/assignment3.cpp", 32, 62});

    report.studentFindings.push_back(
        StudentStyleFinding{"student01", true, true, true, false});
    report.studentFindings.push_back(
        StudentStyleFinding{"student05", true, true, true, true});
    report.studentFindings.push_back(
        StudentStyleFinding{"student09", true, true, true, true});
    report.studentFindings.push_back(
        StudentStyleFinding{"student15", false, false, false, false});
    report.studentFindings.push_back(
        StudentStyleFinding{"student20", true, false, true, true});

    std::ostringstream output;
    printCombinedAnalysisReport(output, report);
    const std::string text = output.str();

    const bool overviewPassed =
        text.find("Student folders analyzed: 22") != std::string::npos &&
        text.find("Source files processed: 66") != std::string::npos &&
        text.find("Source-file pairs compared: 2145") != std::string::npos;

    const bool statisticsPassed =
        text.find("Total source lines: 6973") != std::string::npos &&
        text.find("Recognized function bodies: 242") != std::string::npos;

    const bool clonePassed =
        text.find("Total body-level candidates: 2") != std::string::npos &&
        text.find("Student: student01 | Assignment: assignment3.cpp | lines 4 to 29") != std::string::npos &&
        text.find("Student: student17 | Assignment: assignment3.cpp | lines 4 to 29") != std::string::npos &&
        text.find("Student: student05 | Assignment: assignment3.cpp | lines 34 to 64") != std::string::npos &&
        text.find("Student: student11 | Assignment: assignment3.cpp | lines 32 to 62") != std::string::npos;

    const bool stylePassed =
        text.find("Naming-style deviations: 3") != std::string::npos &&
        text.find("Commenting-style deviations: 3") != std::string::npos &&
        text.find("Naming histories not evaluable: student15") != std::string::npos;

    const bool reviewPassed =
        text.find("Student: student09\n- Historical commenting-style deviation") != std::string::npos &&
        text.find("Student: student17\n- Type-1 body-level candidate") != std::string::npos &&
        text.find("not proof of plagiarism") != std::string::npos;

    AnalysisReport empty;
    std::ostringstream emptyOutput;
    printCombinedAnalysisReport(emptyOutput, empty);
    const bool emptyPassed =
        emptyOutput.str().find("No body-level clone candidates found.") != std::string::npos &&
        emptyOutput.str().find("No clone or stable-history deviation indicators found.") != std::string::npos;

    std::cout << "Dataset overview: " << (overviewPassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Source statistics: " << (statisticsPassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Pairwise clone locations: " << (clonePassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Stylometric evidence: " << (stylePassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Human review indicators: " << (reviewPassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Empty dataset: " << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (overviewPassed && statisticsPassed && clonePassed &&
            stylePassed && reviewPassed && emptyPassed)
               ? 0
               : 1;
}
