#include "type2_clone.hpp"
#include <unordered_map>

bool areType2BodyCandidates(
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

    std::unordered_map<std::string, std::string> forwardMap;
    std::unordered_map<std::string, std::string> reverseMap;
    bool hasRenamedIdentifier = false;

    for (std::size_t i = 0; i < firstLength; ++i)
    {
        const Token &first =
            firstTokens[firstRegion.beginTokenIndex + i];

        const Token &second =
            secondTokens[secondRegion.beginTokenIndex + i];

        if (first.type != second.type)
        {
            return false;
        }

        if (first.type == TokenType::Identifier)
        {
            if (first.lexeme != second.lexeme)
            {
                hasRenamedIdentifier = true;
            }
            auto existing = forwardMap.find(first.lexeme);

            if (existing != forwardMap.end())
            {
                if (existing->second != second.lexeme)
                {
                    return false;
                }
            }
            else
            {
                auto reverseExisting = reverseMap.find(second.lexeme);

                if (reverseExisting != reverseMap.end())
                {
                    return false;
                }

                forwardMap.emplace(first.lexeme, second.lexeme);
                reverseMap.emplace(second.lexeme, first.lexeme);
            }
        }
        else if (first.lexeme != second.lexeme)
        {
            return false;
        }
    }

    return hasRenamedIdentifier;
}

std::vector<Type2BodyMatch> findType2BodyMatches(
    const std::vector<Token> &firstTokens,
    const std::vector<CodeRegion> &firstRegions,
    const std::vector<Token> &secondTokens,
    const std::vector<CodeRegion> &secondRegions)
{
    std::vector<Type2BodyMatch> matches;

    for (const CodeRegion &firstRegion : firstRegions)
    {
        for (const CodeRegion &secondRegion : secondRegions)
        {
            if (areType2BodyCandidates(
                    firstTokens, firstRegion,
                    secondTokens, secondRegion))
            {
                matches.push_back(
                    Type2BodyMatch{firstRegion, secondRegion});
            }
        }
    }

    return matches;
}
