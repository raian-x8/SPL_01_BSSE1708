
#pragma once

#include <vector>
#include "code_region.hpp"

bool areType1BodyCandidates(
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion);
