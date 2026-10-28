#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "type2_clone.hpp"

void printType2BodyMatches(
    std::ostream &output,
    const std::string &firstFileName,
    const std::vector<Token> &firstTokens,
    const std::string &secondFileName,
    const std::vector<Token> &secondTokens,
    const std::vector<Type2BodyMatch> &matches);