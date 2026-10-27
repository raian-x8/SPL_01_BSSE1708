
#include "code_region.hpp"

std::vector<CodeRegion> findBraceRegions(
    const std::vector<Token> &tokens)
{
    std::vector<CodeRegion> regions;
    std::vector<std::size_t> openingBraceIndices;

    for (std::size_t i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i].lexeme == "{")
        {
            openingBraceIndices.push_back(i);
        }
        else if (tokens[i].lexeme == "}" &&
                 !openingBraceIndices.empty())
        {
            std::size_t start = openingBraceIndices.back();
            openingBraceIndices.pop_back();

            regions.push_back(CodeRegion{start, i + 1});
        }
    }

    return regions;
}
