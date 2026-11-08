#include <iostream>

#include "../src/analysis_report.hpp"

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
        "student17/assignment3.cpp", 32, 62});

    report.studentFindings.push_back(
        StudentStyleFinding{"student01", true, true, true, false});

    report.studentFindings.push_back(
        StudentStyleFinding{"student05", true, false, true, true});

    report.studentFindings.push_back(
        StudentStyleFinding{"student15", false, false, false, false});

    const HumanReviewIndicators indicators =
        collectHumanReviewIndicators(report);

    const bool countPassed =
        indicators.size() == 3;

    const bool type1Passed =
        indicators.count("student01") != 0 &&
        indicators.at("student01").count("Type-1 body-level candidate") == 1;

    const bool type2Passed =
        indicators.count("student05") != 0 &&
        indicators.at("student05").count("Type-2-only body-level candidate") == 1;

    const bool namingPassed =
        indicators.count("student01") != 0 &&
        indicators.at("student01").count("Historical naming-style deviation") == 1;

    const bool commentingPassed =
        indicators.count("student05") != 0 &&
        indicators.at("student05").count("Historical commenting-style deviation") == 1;

    const bool nonEvaluablePassed =
        indicators.count("student15") == 0;

    const bool emptyPassed =
        collectHumanReviewIndicators(AnalysisReport{}).empty();

    std::cout << "Distinct review students: "
              << (countPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Type-1 review reason: "
              << (type1Passed ? "PASS" : "FAIL") << '\n';

    std::cout << "Type-2 review reason: "
              << (type2Passed ? "PASS" : "FAIL") << '\n';

    std::cout << "Naming review reason: "
              << (namingPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Commenting review reason: "
              << (commentingPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Non-evaluable student handling: "
              << (nonEvaluablePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty report handling: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (countPassed &&
            type1Passed &&
            type2Passed &&
            namingPassed &&
            commentingPassed &&
            nonEvaluablePassed &&
            emptyPassed)
               ? 0
               : 1;
}