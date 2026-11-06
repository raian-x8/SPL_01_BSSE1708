#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../src/clone_summary.hpp"

int main()
{
    const std::vector<Token> firstTokens = {
        {TokenType::Punctuation, "{", 4, 1},
        {TokenType::Identifier, "first_value", 5, 5},
        {TokenType::Punctuation, "}", 9, 1}};

    const std::vector<Token> secondTokens = {
        {TokenType::Punctuation, "{", 12, 1},
        {TokenType::Identifier, "other_value", 13, 5},
        {TokenType::Punctuation, "}", 18, 1}};

    const CodeRegion validRegion{0, 3};
    const CodeRegion invalidRegion{2, 4};
    std::vector<CloneSummaryEntry> entries;

    const bool type1Added = appendCloneSummaryEntry(
        entries, CloneCandidateKind::Type1,
        "student01/assignment3.cpp", firstTokens, validRegion,
        "student17/assignment3.cpp", secondTokens, validRegion);

    const bool type2Added = appendCloneSummaryEntry(
        entries, CloneCandidateKind::Type2Only,
        "student05/assignment3.cpp", firstTokens, validRegion,
        "student11/assignment3.cpp", secondTokens, validRegion);

    const bool reversedPairAdded = appendCloneSummaryEntry(
        entries, CloneCandidateKind::Type1,
        "student19/assignment3.cpp", secondTokens, validRegion,
        "student03/assignment3.cpp", firstTokens, validRegion);

    const bool invalidRejected = !appendCloneSummaryEntry(
        entries, CloneCandidateKind::Type1,
        "student01/assignment3.cpp", firstTokens, invalidRegion,
        "student17/assignment3.cpp", secondTokens, validRegion);

    std::ostringstream output;
    printCloneSummaryDetails(output, entries);
    const std::string report = output.str();

    const bool locationsPassed =
        report.find("Student: student01 | Assignment: assignment3.cpp | lines 4 to 9") != std::string::npos &&
        report.find("Student: student17 | Assignment: assignment3.cpp | lines 12 to 18") != std::string::npos;

    const bool classificationsPassed =
        report.find("Type-1 candidate pairs:") != std::string::npos &&
        report.find("Type-2-only candidate pairs:") != std::string::npos &&
        report.find("Student: student05") != std::string::npos &&
        report.find("Student: student11") != std::string::npos;

    const bool pairOrderPassed =
        report.find("Student: student03 | Assignment: assignment3.cpp | lines 4 to 9\n"
                    "    Student: student19 | Assignment: assignment3.cpp | lines 12 to 18") != std::string::npos;

    std::ostringstream emptyOutput;
    printCloneSummaryDetails(emptyOutput, {});
    const bool emptyPassed =
        emptyOutput.str().find("No body-level clone candidates found.") != std::string::npos;

    std::cout << "Type-1 summary entry: " << (type1Added ? "PASS" : "FAIL") << '\n';
    std::cout << "Type-2 summary entry: " << (type2Added ? "PASS" : "FAIL") << '\n';
    std::cout << "Canonical pair ordering: " << ((reversedPairAdded && pairOrderPassed) ? "PASS" : "FAIL") << '\n';
    std::cout << "Invalid boundary rejection: " << (invalidRejected ? "PASS" : "FAIL") << '\n';
    std::cout << "Student and line labels: " << (locationsPassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Clone classifications: " << (classificationsPassed ? "PASS" : "FAIL") << '\n';
    std::cout << "Empty summary: " << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (type1Added && type2Added && reversedPairAdded && pairOrderPassed && invalidRejected &&
            locationsPassed && classificationsPassed && emptyPassed)
               ? 0
               : 1;
}
