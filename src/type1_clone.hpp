
#pragma once

#include <vector>
#include "code_region.hpp"

struct Type1BodyMatch
{
    CodeRegion firstRegion;
    CodeRegion secondRegion;
};

bool areType1BodyCandidates(
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion);

std::vector<Type1BodyMatch> findType1BodyMatches(
    const std::vector<Token> &firstTokens,
    const std::vector<CodeRegion> &firstRegions,
    const std::vector<Token> &secondTokens,
    const std::vector<CodeRegion> &secondRegions);
