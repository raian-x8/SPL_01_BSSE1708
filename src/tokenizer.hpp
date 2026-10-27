#pragma once

#include <cstddef>
#include <string>
#include <vector>

enum class TokenType
{
    Keyword,
    Identifier,
    Number,
    StringLiteral,
    CharLiteral,
    Operator,
    Punctuation,
    Unknown
};

struct Token
{
    TokenType type;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

std::vector<Token> tokenize(const std::string &source);