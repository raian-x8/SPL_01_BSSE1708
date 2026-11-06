#include "identifier_style.hpp"

#include <cctype>
#include <unordered_set>

IdentifierStyle classifyIdentifierStyle(
    const std::string &identifier)
{
    if (identifier.empty())
    {
        return IdentifierStyle::Other;
    }

    const unsigned char first =
        static_cast<unsigned char>(identifier.front());

    if (!std::isalpha(first) && identifier.front() != '_')
    {
        return IdentifierStyle::Other;
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasUnderscore = false;

    for (char character : identifier)
    {
        const unsigned char current =
            static_cast<unsigned char>(character);

        if (!std::isalnum(current) && character != '_')
        {
            return IdentifierStyle::Other;
        }

        if (std::isupper(current))
        {
            hasUppercase = true;
        }

        if (std::islower(current))
        {
            hasLowercase = true;
        }

        if (character == '_')
        {
            hasUnderscore = true;
        }
    }

    if (identifier.size() == 1 && std::isalpha(first))
    {
        return IdentifierStyle::SingleLetter;
    }

    if (hasUnderscore)
    {
        if (std::islower(first) &&
            !hasUppercase &&
            identifier.back() != '_' &&
            identifier.find("__") == std::string::npos)
        {
            return IdentifierStyle::SnakeCase;
        }

        return IdentifierStyle::Other;
    }

    if (std::islower(first) && hasUppercase)
    {
        return IdentifierStyle::CamelCase;
    }

    if (std::isupper(first) && hasLowercase)
    {
        return IdentifierStyle::PascalCase;
    }

    if (std::islower(first) && !hasUppercase)
    {
        return IdentifierStyle::Lowercase;
    }

    return IdentifierStyle::Other;
}

IdentifierStyleStatistics calculateIdentifierStyleStatistics(
    const std::vector<Token> &tokens)
{
    IdentifierStyleStatistics statistics;

    std::unordered_set<std::string> seenIdentifiers;

    for (const Token &token : tokens)
    {
        if (token.type != TokenType::Identifier)
        {
            continue;
        }

        if (!seenIdentifiers.insert(token.lexeme).second)
        {
            continue;
        }

        ++statistics.uniqueIdentifierCount;

        statistics.totalIdentifierCharacters +=
            token.lexeme.size();

        switch (classifyIdentifierStyle(token.lexeme))
        {
        case IdentifierStyle::CamelCase:
            ++statistics.camelCase;
            break;

        case IdentifierStyle::PascalCase:
            ++statistics.pascalCase;
            break;

        case IdentifierStyle::SnakeCase:
            ++statistics.snakeCase;
            break;

        case IdentifierStyle::Lowercase:
            ++statistics.lowercase;
            break;

        case IdentifierStyle::SingleLetter:
            ++statistics.singleLetter;
            break;

        case IdentifierStyle::Other:
            ++statistics.other;
            break;
        }
    }

    return statistics;
}

std::string identifierStyleName(
    IdentifierStyle style)
{
    switch (style)
    {
    case IdentifierStyle::CamelCase:
        return "camelCase";

    case IdentifierStyle::PascalCase:
        return "PascalCase";

    case IdentifierStyle::SnakeCase:
        return "snake_case";

    case IdentifierStyle::Lowercase:
        return "lowercase";

    case IdentifierStyle::SingleLetter:
        return "single-letter";

    case IdentifierStyle::Other:
        return "Other";
    }

    return "Other";
}