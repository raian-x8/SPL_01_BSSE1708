#pragma once

#include <vector>
#include "code_region.hpp"

struct Type2BodyMatch
{
    CodeRegion firstRegion;
    CodeRegion secondRegion;
};

bool areType2BodyCandidates(
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion);

std::vector<Type2BodyMatch> findType2BodyMatches(
    const std::vector<Token> &firstTokens,
    const std::vector<CodeRegion> &firstRegions,
    const std::vector<Token> &secondTokens,
    const std::vector<CodeRegion> &secondRegions);