#include "type2_report.hpp"

void printType2BodyMatches(
    std::ostream &output,
    const std::string &firstFileName,
    const std::vector<Token> &firstTokens,
    const std::string &secondFileName,
    const std::vector<Token> &secondTokens,
    const std::vector<Type2BodyMatch> &matches)
{
    output << "CloneScope Type-2 body-level candidate report\n";

    std::size_t reportedCount = 0;

    for (const Type2BodyMatch &match : matches)
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
               << firstStart.line << " to "
               << firstEnd.line << "\n";

        output << secondFileName << ": lines "
               << secondStart.line << " to "
               << secondEnd.line << "\n";

        output << "Evidence: consistent one-to-one identifier renaming "
               << "with matching non-identifier token lexemes.\n";

        output << "Classification: Type-2-only body candidate.\n";

        output << "Human review required; "
               << "similarity is not proof of plagiarism.\n";
    }

    output << "\nReported candidates: "
           << reportedCount << "\n";
}