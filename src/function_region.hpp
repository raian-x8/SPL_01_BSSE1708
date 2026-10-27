
#pragma once

#include <vector>
#include "code_region.hpp"

std::vector<CodeRegion> findFunctionBodyRegions(
    const std::vector<Token> &tokens);
