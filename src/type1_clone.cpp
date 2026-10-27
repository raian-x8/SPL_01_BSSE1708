
#include "type1_clone.hpp"

bool areType1BodyCandidates(
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion)
{
    if (firstRegion.beginTokenIndex >= firstRegion.endTokenIndex ||
        secondRegion.beginTokenIndex >= secondRegion.endTokenIndex ||
        firstRegion.endTokenIndex > firstTokens.size() ||
        secondRegion.endTokenIndex > secondTokens.size())
    {
        return false;
    }

    std::size_t firstLength =
        firstRegion.endTokenIndex - firstRegion.beginTokenIndex;

    std::size_t secondLength =
        secondRegion.endTokenIndex - secondRegion.beginTokenIndex;

    if (firstLength != secondLength)
    {
        return false;
    }

    for (std::size_t i = 0; i < firstLength; ++i)
    {
        const Token &first =
            firstTokens[firstRegion.beginTokenIndex + i];

        const Token &second =
            secondTokens[secondRegion.beginTokenIndex + i];

        if (first.type != second.type ||
            first.lexeme != second.lexeme)
        {
            return false;
        }
    }

    return true;
}

std::vector<Type1BodyMatch> findType1BodyMatches(
    const std::vector<Token> &firstTokens,
    const std::vector<CodeRegion> &firstRegions,
    const std::vector<Token> &secondTokens,
    const std::vector<CodeRegion> &secondRegions)
{
    std::vector<Type1BodyMatch> matches;

    for (const CodeRegion &firstRegion : firstRegions)
    {
        for (const CodeRegion &secondRegion : secondRegions)
        {
            if (areType1BodyCandidates(
                    firstTokens, firstRegion,
                    secondTokens, secondRegion))
            {
                matches.push_back(
                    Type1BodyMatch{firstRegion, secondRegion});
            }
        }
    }

    return matches;
}
