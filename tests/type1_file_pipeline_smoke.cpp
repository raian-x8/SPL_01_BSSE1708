
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../src/preprocessor.hpp"
#include "../src/tokenizer.hpp"
#include "../src/function_region.hpp"
#include "../src/type1_clone.hpp"
#include "../src/type1_report.hpp"

int main()
{
    std::ifstream firstFile(
        "tests/fixtures/type1/student_a.cpp");

    std::ifstream secondFile(
        "tests/fixtures/type1/student_b.cpp");

    assert(firstFile.is_open());
    assert(secondFile.is_open());

    std::ostringstream firstBuffer;
    firstBuffer << firstFile.rdbuf();

    std::ostringstream secondBuffer;
    secondBuffer << secondFile.rdbuf();

    std::string firstSource = firstBuffer.str();
    std::string secondSource = secondBuffer.str();

    assert(!firstSource.empty());
    assert(!secondSource.empty());

    std::vector<Token> firstTokens =
        tokenize(removeComments(firstSource));

    std::vector<Token> secondTokens =
        tokenize(removeComments(secondSource));

    assert(firstTokens.size() == 16);
    assert(secondTokens.size() == 16);

    std::vector<CodeRegion> firstFunctionRegions =
        findFunctionBodyRegions(firstTokens);

    std::vector<CodeRegion> secondFunctionRegions =
        findFunctionBodyRegions(secondTokens);

    assert(firstFunctionRegions.size() == 1);
    assert(secondFunctionRegions.size() == 1);

    assert(firstFunctionRegions[0].beginTokenIndex == 9);
    assert(firstFunctionRegions[0].endTokenIndex == 16);

    assert(secondFunctionRegions[0].beginTokenIndex == 9);
    assert(secondFunctionRegions[0].endTokenIndex == 16);

    bool type1Match = areType1BodyCandidates(
        firstTokens, firstFunctionRegions[0],
        secondTokens, secondFunctionRegions[0]);

    assert(type1Match);

    std::ifstream realisticFirstFile(
        "tests/fixtures/type1/realistic_student_a.cpp");

    std::ifstream realisticSecondFile(
        "tests/fixtures/type1/realistic_student_b.cpp");

    assert(realisticFirstFile.is_open());
    assert(realisticSecondFile.is_open());

    std::ostringstream realisticFirstBuffer;
    realisticFirstBuffer << realisticFirstFile.rdbuf();

    std::ostringstream realisticSecondBuffer;
    realisticSecondBuffer << realisticSecondFile.rdbuf();

    std::vector<Token> realisticFirstTokens =
        tokenize(removeComments(realisticFirstBuffer.str()));

    std::vector<Token> realisticSecondTokens =
        tokenize(removeComments(realisticSecondBuffer.str()));

    assert(!realisticFirstTokens.empty());
    assert(!realisticSecondTokens.empty());

    std::vector<CodeRegion> realisticFirstRegions =
        findFunctionBodyRegions(realisticFirstTokens);

    std::vector<CodeRegion> realisticSecondRegions =
        findFunctionBodyRegions(realisticSecondTokens);

    assert(realisticFirstRegions.size() == 2);
    assert(realisticSecondRegions.size() == 2);

    bool addMatch = areType1BodyCandidates(
        realisticFirstTokens, realisticFirstRegions[0],
        realisticSecondTokens, realisticSecondRegions[0]);

    bool mainMatch = areType1BodyCandidates(
        realisticFirstTokens, realisticFirstRegions[1],
        realisticSecondTokens, realisticSecondRegions[1]);

    assert(addMatch);
    assert(!mainMatch);

    std::size_t candidateCount = 0;

    for (const CodeRegion &firstRegion : realisticFirstRegions)
    {
        for (const CodeRegion &secondRegion : realisticSecondRegions)
        {
            if (areType1BodyCandidates(
                    realisticFirstTokens, firstRegion,
                    realisticSecondTokens, secondRegion))
            {
                ++candidateCount;
            }
        }
    }

    assert(candidateCount == 1);

    std::vector<Type1BodyMatch> matches = findType1BodyMatches(
        realisticFirstTokens, realisticFirstRegions,
        realisticSecondTokens, realisticSecondRegions);

    assert(matches.size() == 1);

    assert(matches[0].firstRegion.beginTokenIndex ==
           realisticFirstRegions[0].beginTokenIndex);

    assert(matches[0].firstRegion.endTokenIndex ==
           realisticFirstRegions[0].endTokenIndex);

    assert(matches[0].secondRegion.beginTokenIndex ==
           realisticSecondRegions[0].beginTokenIndex);

    assert(matches[0].secondRegion.endTokenIndex ==
           realisticSecondRegions[0].endTokenIndex);

    const CodeRegion &firstMatchedRegion = matches[0].firstRegion;
    const CodeRegion &secondMatchedRegion = matches[0].secondRegion;

    const Token &firstStart =
        realisticFirstTokens[firstMatchedRegion.beginTokenIndex];

    const Token &firstEnd =
        realisticFirstTokens[firstMatchedRegion.endTokenIndex - 1];

    const Token &secondStart =
        realisticSecondTokens[secondMatchedRegion.beginTokenIndex];

    const Token &secondEnd =
        realisticSecondTokens[secondMatchedRegion.endTokenIndex - 1];

    assert(firstStart.lexeme == "{");
    assert(firstEnd.lexeme == "}");
    assert(secondStart.lexeme == "{");
    assert(secondEnd.lexeme == "}");

    std::cout << "Type-1 matching body locations:\n";

    std::cout << "Student A: lines "
              << firstStart.line << " to " << firstEnd.line << "\n";

    std::cout << "Student B: lines "
              << secondStart.line << " to " << secondEnd.line << "\n";

    std::ostringstream reportBuffer;

    printType1BodyMatches(
        reportBuffer,
        "realistic_student_a.cpp",
        realisticFirstTokens,
        "realistic_student_b.cpp",
        realisticSecondTokens,
        matches);

    std::string reportText = reportBuffer.str();

    assert(reportText.find(
               "realistic_student_a.cpp: lines 7 to 9") != std::string::npos);

    assert(reportText.find(
               "realistic_student_b.cpp: lines 10 to 13") != std::string::npos);

    assert(reportText.find("Reported candidates: 1") != std::string::npos);

    std::cout << "\n"
              << reportText;

    std::cout << "Type-1 file pipeline smoke test passed.\n";

    return 0;
}
