#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../src/tokenizer.hpp"
#include "../src/type2_report.hpp"

int main()
{
    const std::vector<Token> firstTokens =
        tokenize("return a + b;");

    const std::vector<Token> secondTokens =
        tokenize("return x + y;");

    const CodeRegion firstRegion{0, firstTokens.size()};
    const CodeRegion secondRegion{0, secondTokens.size()};

    const std::vector<Type2BodyMatch> matches{
        Type2BodyMatch{firstRegion, secondRegion}};

    std::ostringstream output;

    printType2BodyMatches(
        output,
        "student1/demo.c",
        firstTokens,
        "student2/demo.c",
        secondTokens,
        matches);

    const std::string report = output.str();

    bool pathsCorrect =
        report.find("student1/demo.c") != std::string::npos &&
        report.find("student2/demo.c") != std::string::npos;

    bool classificationCorrect =
        report.find("Type-2-only body candidate") != std::string::npos;

    bool warningPresent =
        report.find("similarity is not proof of plagiarism") !=
        std::string::npos;

    bool countCorrect =
        report.find("Reported candidates: 1") != std::string::npos;

    const CodeRegion invalidRegion{
        0, firstTokens.size() + 1};

    const std::vector<Type2BodyMatch> invalidMatches{
        Type2BodyMatch{invalidRegion, secondRegion}};

    std::ostringstream invalidOutput;

    printType2BodyMatches(
        invalidOutput,
        "student1/demo.c",
        firstTokens,
        "student2/demo.c",
        secondTokens,
        invalidMatches);

    const std::string invalidReport = invalidOutput.str();

    bool invalidRegionRejected =
        invalidReport.find("Warning: skipped invalid match boundaries.") !=
            std::string::npos &&
        invalidReport.find("Reported candidates: 0") !=
            std::string::npos &&
        invalidReport.find("Candidate #1") ==
            std::string::npos;

    std::cout << "Source paths: "
              << (pathsCorrect ? "PASS" : "FAIL") << '\n';

    std::cout << "Type-2 classification: "
              << (classificationCorrect ? "PASS" : "FAIL") << '\n';

    std::cout << "Human-review warning: "
              << (warningPresent ? "PASS" : "FAIL") << '\n';

    std::cout << "Reported candidate count: "
              << (countCorrect ? "PASS" : "FAIL") << '\n';

    std::cout << "Invalid report region rejected: "
              << (invalidRegionRejected ? "PASS" : "FAIL") << '\n';

    return (pathsCorrect && classificationCorrect &&
            warningPresent && countCorrect &&
            invalidRegionRejected)
               ? 0
               : 1;
}