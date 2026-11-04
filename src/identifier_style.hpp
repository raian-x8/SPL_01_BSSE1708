#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "tokenizer.hpp"

enum class IdentifierStyle
{
    CamelCase,
    PascalCase,
    SnakeCase,
    Lowercase,
    SingleLetter,
    Other
};

IdentifierStyle classifyIdentifierStyle(
    const std::string &identifier);

struct IdentifierStyleStatistics
{
    std::size_t uniqueIdentifierCount = 0;
    std::size_t totalIdentifierCharacters = 0;

    std::size_t camelCase = 0;
    std::size_t pascalCase = 0;
    std::size_t snakeCase = 0;
    std::size_t lowercase = 0;
    std::size_t singleLetter = 0;
    std::size_t other = 0;
};

IdentifierStyleStatistics calculateIdentifierStyleStatistics(
    const std::vector<Token> &tokens);