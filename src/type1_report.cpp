
#include "type1_report.hpp"

void printType1BodyMatches(
    std::ostream &output,
    const std::string &firstFileName,
    const std::vector<Token> &firstTokens,
    const std::string &secondFileName,
    const std::vector<Token> &secondTokens,
    const std::vector<Type1BodyMatch> &matches)
{
    output << "CloneScope Type-1 body-level candidate report\n";

    std::size_t reportedCount = 0;

    for (const Type1BodyMatch &match : matches)
    {
        const CodeRegion &first = match.firstRegion;
        const CodeRegion &second = match.secondRegion;

        if (first.beginTokenIndex >= first.endTokenIndex ||
            first.endTokenIndex > firstTokens.size() ||
            second.beginTokenIndex >= second.endTokenIndex ||
            second.endTokenIndex > secondTokens.size())
        {
            output << "Warning: skipped invalid match boundaries.\n";
            continue;
        }

        const Token &firstStart =
            firstTokens[first.beginTokenIndex];

        const Token &firstEnd =
            firstTokens[first.endTokenIndex - 1];

        const Token &secondStart =
            secondTokens[second.beginTokenIndex];

        const Token &secondEnd =
            secondTokens[second.endTokenIndex - 1];

        ++reportedCount;

        output << "\nCandidate #" << reportedCount << "\n";

        output << firstFileName << ": lines "
               << firstStart.line << " to " << firstEnd.line << "\n";

        output << secondFileName << ": lines "
               << secondStart.line << " to " << secondEnd.line << "\n";

        output << "Evidence: identical body token types and lexemes.\n";
        output << "Human review required; similarity is not proof of plagiarism.\n";
    }

    output << "\nReported candidates: " << reportedCount << "\n";
}
