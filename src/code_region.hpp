
#pragma once

#include <cstddef>
#include <vector>
#include "tokenizer.hpp"

struct CodeRegion
{
    std::size_t beginTokenIndex;
    std::size_t endTokenIndex;
};

std::vector<CodeRegion> findBraceRegions(
    const std::vector<Token> &tokens);
