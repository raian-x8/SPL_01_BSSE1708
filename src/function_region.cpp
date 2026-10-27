
#include "function_region.hpp"

std::vector<CodeRegion> findFunctionBodyRegions(
    const std::vector<Token> &tokens)
{
    std::vector<CodeRegion> functionRegions;
    std::vector<CodeRegion> braceRegions = findBraceRegions(tokens);

    for (const CodeRegion &region : braceRegions)
    {
        std::size_t braceIndex = region.beginTokenIndex;

        if (braceIndex == 0 || tokens[braceIndex - 1].lexeme != ")")
        {
            continue;
        }

        std::size_t depth = 0;
        std::size_t openParenIndex = tokens.size();

        for (std::size_t i = braceIndex; i > 0; --i)
        {
            std::size_t index = i - 1;

            if (tokens[index].lexeme == ")")
            {
                ++depth;
            }
            else if (tokens[index].lexeme == "(")
            {
                --depth;

                if (depth == 0)
                {
                    openParenIndex = index;
                    break;
                }
            }
        }

        if (openParenIndex == tokens.size() || openParenIndex == 0)
        {
            continue;
        }

        if (tokens[openParenIndex - 1].type == TokenType::Identifier)
        {
            functionRegions.push_back(region);
        }
    }

    return functionRegions;
}
